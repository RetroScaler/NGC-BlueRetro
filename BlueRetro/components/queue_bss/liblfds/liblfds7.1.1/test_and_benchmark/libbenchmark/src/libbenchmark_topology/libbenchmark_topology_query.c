/***** includes *****/
#include "libbenchmark_topology_internal.h"





/****************************************************************************/
void libbenchmark_topology_query( struct libbenchmark_topology_state *ts, enum libbenchmark_topology_query query_type, void *query_input, void *query_output )
{
  LFDS711_PAL_ASSERT( ts != NULL );

  // TRD : query type can be any value in its range
  // TRD : query_input can be NULL in some cases
  // TRD : query_outputput can be NULL in some cases

  switch( query_type )
  {
    case LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMBER_OF_NODE_TYPE:
    {
      enum libbenchmark_topology_node_type
        type;

      lfds711_pal_uint_t
        *count;

      struct lfds711_btree_au_element
        *baue = NULL;

      struct libbenchmark_topology_node_state
        *tns;

      // TRD : query_input is an enum and so can be 0
      LFDS711_PAL_ASSERT( query_output != NULL );

      type = (enum libbenchmark_topology_node_type) (lfds711_pal_uint_t) query_input;
      count = (lfds711_pal_uint_t *) query_output;

      *count = 0;

      while( lfds711_btree_au_get_by_absolute_position_and_then_by_relative_position(&ts->topology_tree, &baue, LFDS711_BTREE_AU_ABSOLUTE_POSITION_LARGEST_IN_TREE, LFDS711_BTREE_AU_RELATIVE_POSITION_NEXT_SMALLER_ELEMENT_IN_ENTIRE_TREE) )
      {
        tns = LFDS711_BTREE_AU_GET_VALUE_FROM_ELEMENT( *baue );

        if( tns->type == type )
          (*count)++;
      }
    }
    break;

    case LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMA_NODE_FOR_LOGICAL_PROCESSOR:
    {
      struct lfds711_btree_au_element
        *baue;

      struct libbenchmark_topology_node_state
        *tns_lp,
        *tns = NULL;

      LFDS711_PAL_ASSERT( query_input != NULL );
      LFDS711_PAL_ASSERT( query_output != NULL );

      *(struct libbenchmark_topology_node_state **) query_output = NULL;

      tns_lp = (struct libbenchmark_topology_node_state *) query_input;

      // TRD : find the LP, the climb the tree to the first larger NUMA node

      lfds711_btree_au_get_by_key( &ts->topology_tree, NULL, tns_lp, &baue );

      while( lfds711_btree_au_get_by_relative_position(&baue,LFDS711_BTREE_AU_RELATIVE_POSITION_NEXT_LARGER_ELEMENT_IN_ENTIRE_TREE) )
      {
        tns = LFDS711_BTREE_AU_GET_VALUE_FROM_ELEMENT( *baue );

        if( tns->type == LIBBENCHMARK_TOPOLOGY_NODE_TYPE_NUMA )
          break;
      }

      if( tns->type == LIBBENCHMARK_TOPOLOGY_NODE_TYPE_NUMA )
        *(struct libbenchmark_topology_node_state **) query_output = tns;
    }
    break;
  }

  return;
}

