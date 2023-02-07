/***** includes *****/
#include "libbenchmark_benchmarksuite_internal.h"





/****************************************************************************/
void libbenchmark_benchmarksuite_run( struct libbenchmark_benchmarksuite_state *bss, struct libbenchmark_results_state *rs )
{
  char
    *topology_string;

  struct libbenchmark_benchmarkset_state
    *bsets;

  struct lfds711_list_asu_element
    *lasue = NULL;

  LFDS711_PAL_ASSERT( bss != NULL );
  LFDS711_PAL_ASSERT( rs != NULL );

  topology_string = libbenchmark_topology_generate_string( bss->ts, bss->ms, LIBBENCHMARK_TOPOLOGY_STRING_FORMAT_STDOUT );

  libbenchmark_pal_print_string( topology_string );

  // TRD : iterate over all benchmarksets
  while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(bss->benchmarksets,lasue) )
  {
    bsets = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );

    libbenchmark_benchmarkset_run( bsets, rs );
  }

  return;
}

