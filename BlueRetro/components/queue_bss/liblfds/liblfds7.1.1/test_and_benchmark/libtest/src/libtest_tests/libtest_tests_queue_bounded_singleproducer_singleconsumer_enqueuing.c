/***** includes *****/
#include "libtest_tests_internal.h"





/****************************************************************************/
#pragma warning( disable : 4100 )

void libtest_tests_queue_bss_enqueuing( struct lfds711_list_asu_state *list_of_logical_processors, struct libshared_memory_state *ms, enum lfds711_misc_validity *dvs )
{
  int
    rv;

  lfds711_pal_uint_t
    loop;

  struct lfds711_queue_bss_element
    element_array[128];

  struct lfds711_queue_bss_state
    qs;

  struct lfds711_misc_validation_info
    vi;

  LFDS711_PAL_ASSERT( list_of_logical_processors != NULL );
  LFDS711_PAL_ASSERT( ms != NULL );
  LFDS711_PAL_ASSERT( dvs != NULL );

  /* TRD : create an empty queue
           enqueue 128 elements
           it's a single producer queue, so we just do this in our current thread
           it's an API test
  */

  *dvs = LFDS711_MISC_VALIDITY_VALID;

  lfds711_queue_bss_init_valid_on_current_logical_core( &qs, element_array, 128, NULL );

  for( loop = 0 ; loop < 127 ; loop++ )
    if( 1 != lfds711_queue_bss_enqueue(&qs, NULL, (void *) loop) )
      *dvs = LFDS711_MISC_VALIDITY_INVALID_TEST_DATA;

  // TRD : at this point enqueuing one more should return 0
  rv = lfds711_queue_bss_enqueue( &qs, NULL, (void *) loop );

  if( rv != 0 )
    *dvs = LFDS711_MISC_VALIDITY_INVALID_TEST_DATA;

  vi.min_elements = vi.max_elements = 127;

  lfds711_queue_bss_query( &qs, LFDS711_QUEUE_BSS_QUERY_VALIDATE, &vi, dvs );

  lfds711_queue_bss_cleanup( &qs, NULL );

  return;
}

#pragma warning( default : 4100 )

