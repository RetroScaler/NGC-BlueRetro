/***** includes *****/
#include "libtest_testsuite_internal.h"





/****************************************************************************/
void libtest_testsuite_cleanup( struct libtest_testsuite_state *ts )
{
  LFDS711_PAL_ASSERT( ts != NULL );

  lfds711_list_asu_cleanup( &ts->list_of_logical_processors, NULL );

  return;
}

