/***** includes *****/
#include "libtest_tests_internal.h"

/***** structs *****/
struct test_per_thread_state
{
  struct lfds711_freelist_state
    *fs;
};

struct test_element
{
  struct lfds711_freelist_element
    fe;

  lfds711_pal_uint_t
    datum;
};

/***** private prototypes *****/
static libshared_pal_thread_return_t LIBSHARED_PAL_THREAD_CALLING_CONVENTION thread_rapid_popping_and_pushing( void *libshared_threads_thread_state );





/****************************************************************************/
void libtest_tests_freelist_without_ea_rapid_popping_and_pushing( struct lfds711_list_asu_state *list_of_logical_processors, struct libshared_memory_state *ms, enum lfds711_misc_validity *dvs )
{
  lfds711_pal_uint_t
    index = 0,
    loop,
    number_logical_processors;

  struct lfds711_list_asu_element
    *lasue = NULL;

  struct lfds711_misc_validation_info
    vi = { 0, 0 };

  struct lfds711_freelist_state
    fs;

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

  /* TRD : in these tests there is a fundamental antagonism between
           how much checking/memory clean up that we do and the
           likelyhood of collisions between threads in their lock-free
           operations

           the lock-free operations are very quick; if we do anything
           much at all between operations, we greatly reduce the chance
           of threads colliding

           so we have some tests which do enough checking/clean up that
           they can tell the freelist is valid and don't leak memory
           and here, this test now is one of thofe which does minimal
           checking - in fact, the nature of the test is that you can't
           do any real checking - but goes very quickly

           what we do is create a small freelist and then run one thread
           per CPU, where each thread simply pushes and then immediately
           pops

           the test runs for ten feconds

           after the test is done, the only check we do is to traverfe
           the freelist, checking for loops and ensuring the number of
           elements is correct
  */

  *dvs = LFDS711_MISC_VALIDITY_VALID;

  lfds711_list_asu_query( list_of_logical_processors, LFDS711_LIST_ASU_QUERY_GET_POTENTIALLY_INACCURATE_COUNT, NULL, (void **) &number_logical_processors );

  // TRD : allocate
  tpts = libshared_memory_alloc_from_unknown_node( ms, sizeof(struct test_per_thread_state) * number_logical_processors, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
  pts = libshared_memory_alloc_from_unknown_node( ms, sizeof(struct libtest_threadset_per_thread_state) * number_logical_processors, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
  te_array = libshared_memory_alloc_from_unknown_node( ms, sizeof(struct test_element) * number_logical_processors, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );

  lfds711_freelist_init_valid_on_current_logical_core( &fs, NULL, 0, NULL );

  for( loop = 0 ; loop < number_logical_processors ; loop++ )
    tpts[loop].fs = &fs;

  for( loop = 0 ; loop < number_logical_processors ; loop++ )
  {
    LFDS711_FREELIST_SET_VALUE_IN_ELEMENT( te_array[loop].fe, &te_array[loop] );
    lfds711_freelist_push( &fs, &te_array[loop].fe, NULL );
  }

  // TRD : get the threads ready
  libtest_threadset_init( &ts, NULL );

  while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(*list_of_logical_processors,lasue) )
  {
    lp = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
    libtest_threadset_add_thread( &ts, &pts[index], lp, thread_rapid_popping_and_pushing, &tpts[index] );
    index++;
  }

  // TRD : run the test
  libtest_threadset_run( &ts );

  libtest_threadset_cleanup( &ts );

  // TRD : validate
  LFDS711_MISC_BARRIER_LOAD;

  vi.min_elements = vi.max_elements = number_logical_processors;

  lfds711_freelist_query( &fs, LFDS711_FREELIST_QUERY_SINGLETHREADED_VALIDATE, &vi, dvs );

  lfds711_freelist_cleanup( &fs, NULL );

  return;
}





/****************************************************************************/
static libshared_pal_thread_return_t LIBSHARED_PAL_THREAD_CALLING_CONVENTION thread_rapid_popping_and_pushing( void *libtest_threadset_per_thread_state )
{
  lfds711_pal_uint_t
    time_loop = 0;

  struct lfds711_freelist_element
    *fe;

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
    lfds711_freelist_pop( tpts->fs, &fe, NULL );
    lfds711_freelist_push( tpts->fs, fe, NULL );

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

