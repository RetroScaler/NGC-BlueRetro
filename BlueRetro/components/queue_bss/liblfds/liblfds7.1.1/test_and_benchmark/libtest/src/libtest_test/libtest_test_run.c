/***** includes *****/
#include "libtest_test_internal.h"





/****************************************************************************/
void libtest_test_run( struct libtest_test_state *ts,
                       struct lfds711_list_asu_state *list_of_logical_processors,
                       struct libshared_memory_state *ms,
                       enum lfds711_misc_validity *dvs )
{
  LFDS711_PAL_ASSERT( ts != NULL );
  LFDS711_PAL_ASSERT( list_of_logical_processors != NULL );
  LFDS711_PAL_ASSERT( ms != NULL );
  LFDS711_PAL_ASSERT( dvs != NULL );

  ts->test_function( list_of_logical_processors, ms, dvs );

  return;
}

