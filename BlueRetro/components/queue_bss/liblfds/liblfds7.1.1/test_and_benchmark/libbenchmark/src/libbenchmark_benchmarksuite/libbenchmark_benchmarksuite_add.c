/***** includes *****/
#include "libbenchmark_benchmarksuite_internal.h"





/****************************************************************************/
void libbenchmark_benchmarksuite_add_benchmarkset( struct libbenchmark_benchmarksuite_state *bss,
                                                   struct libbenchmark_benchmarkset_state *bsets )
{
  LFDS711_PAL_ASSERT( bss != NULL );
  LFDS711_PAL_ASSERT( bsets != NULL );

  LFDS711_LIST_ASU_SET_VALUE_IN_ELEMENT( bsets->lasue, bsets );
  lfds711_list_asu_insert_at_end( &bss->benchmarksets, &bsets->lasue );

  return;
}

