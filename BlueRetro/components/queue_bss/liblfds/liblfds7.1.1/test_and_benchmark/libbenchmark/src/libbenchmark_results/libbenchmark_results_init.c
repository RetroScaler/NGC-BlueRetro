/***** includes *****/
#include "libbenchmark_results_internal.h"





/****************************************************************************/
void libbenchmark_results_init( struct libbenchmark_results_state *rs,
                                struct libshared_memory_state *ms )
{
  LFDS711_PAL_ASSERT( rs != NULL );
  LFDS711_PAL_ASSERT( ms != NULL );

  lfds711_btree_au_init_valid_on_current_logical_core( &rs->results_tree, libbenchmark_result_compare_function, LFDS711_BTREE_AU_EXISTING_KEY_FAIL, NULL );

  rs->ms = ms;

  return;
}

