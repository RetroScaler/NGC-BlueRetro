/***** includes *****/
#include "libbenchmark_topology_node_internal.h"





/****************************************************************************/
void libbenchmark_topology_node_cleanup( struct libbenchmark_topology_node_state *tns, void (*element_cleanup_callback)(struct lfds711_list_aso_state *lasos, struct lfds711_list_aso_element *lasoe) )
{
  LFDS711_PAL_ASSERT( tns != NULL );
  // TRD : element_cleanup_callback can be NULL

  lfds711_list_aso_cleanup( &tns->logical_processor_children, element_cleanup_callback );

  return;
}

