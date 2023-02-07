/***** includes *****/
#include "libtest_tests_internal.h"

/***** structs *****/
struct test_per_thread_state
{
  enum flag
    error_flag;

  lfds711_pal_uint_t
    counter,
    number_logical_processors,
    *per_thread_counters,
    thread_number;

  struct lfds711_queue_umm_state
    *qs;
};

struct test_element
{
  struct lfds711_queue_umm_element
    qe,
    *qe_use;

  lfds711_pal_uint_t
    counter,
    thread_number;
};

/***** private prototypes *****/
static libshared_pal_thread_return_t LIBSHARED_PAL_THREAD_CALLING_CONVENTION thread_enqueuer_and_dequeuer( void *libtest_threadset_per_thread_state );





/****************************************************************************/
void libtest_tests_queue_umm_enqueuing_and_dequeuing( struct lfds711_list_asu_state *list_of_logical_processors, struct libshared_memory_state *ms, enum lfds711_misc_validity *dvs )
{
  lfds711_pal_uint_t
    loop,
    number_elements,
    number_logical_processors,
    *per_thread_counters,
    subloop;

  struct lfds711_list_asu_element
    *lasue = NULL;

  struct lfds711_queue_umm_state
    qs;

  struct lfds711_misc_validation_info
    vi;

  struct libtest_logical_processor
    *lp;

  struct libtest_threadset_per_thread_state
    *pts;

  struct libtest_threadset_state
    ts;

  struct test_element
    *te_array;

  struct test_per_thread_state
    *tpts;

  LFDS711_PAL_ASSERT( list_of_logical_processors != NULL );
  LFDS711_PAL_ASSERT( ms != NULL );
  LFDS711_PAL_ASSERT( dvs != NULL );

  /* TRD : create a queue with one element per thread
           each thread constly dequeues and enqueues from that one queue
           where when enqueuing sets in the element
           its thread number and counter
           and when dequeuing, checks the thread number and counter
           against previously seen counter for that thread
           where it should always see a higher number
  */

  *dvs = LFDS711_MISC_VALIDITY_VALID;

  // TRD : allocate
  lfds711_list_asu_query( list_of_logical_processors, LFDS711_LIST_ASU_QUERY_GET_POTENTIALLY_INACCURATE_COUNT, NULL, (void **) &number_logical_processors );
  tpts = libshared_memory_alloc_from_unknown_node( ms, sizeof(struct test_per_thread_state) * number_logical_processors, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
  pts = libshared_memory_alloc_from_unknown_node( ms, sizeof(struct libtest_threadset_per_thread_state) * number_logical_processors, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
  per_thread_counters = libshared_memory_alloc_from_unknown_node( ms, sizeof(lfds711_pal_uint_t) * number_logical_processors * number_logical_processors, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
  te_array = libshared_memory_alloc_largest_possible_array_from_unknown_node( ms, sizeof(struct test_element), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES, &number_elements );

  lfds711_queue_umm_init_valid_on_current_logical_core( &qs, &(te_array+number_logical_processors)->qe, NULL );

  // TRD : we assume the test will iterate at least once (or we'll have a false negative)
  for( loop = 0 ; loop < number_logical_processors ; loop++ )
  {
    (te_array+loop)->thread_number = loop;
    (te_array+loop)->counter = 0;
    LFDS711_QUEUE_UMM_SET_VALUE_IN_ELEMENT( (te_array+loop)->qe, te_array+loop );
    lfds711_queue_umm_enqueue( &qs, &(te_array+loop)->qe );
  }

  libtest_threadset_init( &ts, NULL );

  loop = 0;

  while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(*list_of_logical_processors,lasue) )
  {
    lp = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
    (tpts+loop)->qs = &qs;
    (tpts+loop)->thread_number = loop;
    (tpts+loop)->counter = 0;
    (tpts+loop)->error_flag = LOWERED;
    (tpts+loop)->per_thread_counters = per_thread_counters + loop * number_logical_processors;
    (tpts+loop)->number_logical_processors = number_logical_processors;

    for( subloop = 0 ; subloop < number_logical_processors ; subloop++ )
      *((tpts+loop)->per_thread_counters+subloop) = 0;

    libtest_threadset_add_thread( &ts, &pts[loop], lp, thread_enqueuer_and_dequeuer, &tpts[loop] );
    loop++;
  }

  LFDS711_MISC_BARRIER_STORE;

  lfds711_misc_force_store();

  // TRD : run the test
  libtest_threadset_run( &ts );

  libtest_threadset_cleanup( &ts );

  // TRD : validate
  LFDS711_MISC_BARRIER_LOAD;

  vi.min_elements = vi.max_elements = number_logical_processors;

  lfds711_queue_umm_query( &qs, LFDS711_QUEUE_UMM_QUERY_SINGLETHREADED_VALIDATE, &vi, dvs );

  for( loop = 0 ; loop < number_logical_processors ; loop++ )
    if( (tpts+loop)->error_flag == RAISED )
      *dvs = LFDS711_MISC_VALIDITY_INVALID_TEST_DATA;

  lfds711_queue_umm_cleanup( &qs, NULL );

  return;
}





/****************************************************************************/
static libshared_pal_thread_return_t LIBSHARED_PAL_THREAD_CALLING_CONVENTION thread_enqueuer_and_dequeuer( void *libtest_threadset_per_thread_state )
{
  lfds711_pal_uint_t
    time_loop = 0;

  struct lfds711_queue_umm_element
    *qe;

  struct test_element
    *te;

  struct test_per_thread_state
    *tpts;

  struct libtest_threadset_per_thread_state
    *pts;

  time_t
    current_time,
    start_time;

  LFDS711_MISC_MAKE_VALID_ON_CURRENT_LOGICAL_CORE_INITS_COMPLETED_BEFORE_NOW_ON_ANY_OTHER_LOGICAL_CORE;

  LFDS711_PAL_ASSERT( libtest_threadset_per_thread_state != NULL );

  pts = (struct libtest_threadset_per_thread_state *) libtest_threadset_per_thread_state;
  tpts = LIBTEST_THREADSET_GET_USER_STATE_FROM_PER_THREAD_STATE( *pts );

  libtest_threadset_thread_ready_and_wait( pts );

  current_time = start_time = time( NULL );

  while( current_time < start_time + TEST_DURATION_IN_SECONDS )
  {
    lfds711_queue_umm_dequeue( tpts->qs, &qe );
    te = LFDS711_QUEUE_UMM_GET_VALUE_FROM_ELEMENT( *qe );

    if( te->thread_number >= tpts->number_logical_processors )
      tpts->error_flag = RAISED;
    else
    {
      if( te->counter < tpts->per_thread_counters[te->thread_number] )
        tpts->error_flag = RAISED;

      if( te->counter >= tpts->per_thread_counters[te->thread_number] )
        tpts->per_thread_counters[te->thread_number] = te->counter+1;
    }

    te->thread_number = tpts->thread_number;
    te->counter = ++tpts->counter;

    LFDS711_QUEUE_UMM_SET_VALUE_IN_ELEMENT( *qe, te );
    lfds711_queue_umm_enqueue( tpts->qs, qe );

    if( time_loop++ == TIME_LOOP_COUNT )
    {
      time_loop = 0;
      time( &current_time );
    }
  }

  LFDS711_MISC_BARRIER_STORE;

  lfds711_misc_force_store();

  return LIBSHARED_PAL_THREAD_RETURN_CAST(RETURN_SUCCESS);
}

