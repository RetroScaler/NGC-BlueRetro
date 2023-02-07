/***** includes *****/
#include "libbenchmark_topology_internal.h"





/****************************************************************************/
void libbenchmark_topology_generate_numa_modes_list( struct libbenchmark_topology_state *ts, enum libbenchmark_topology_numa_mode numa_mode, struct libshared_memory_state *ms, struct lfds711_list_asu_state *numa_modes_list )
{
  lfds711_pal_uint_t
    numa_node_count;

  struct libbenchmark_topology_numa_node
    *tnn;

  LFDS711_PAL_ASSERT( ts != NULL );
  LFDS711_PAL_ASSERT( numa_mode == LIBBENCHMARK_TOPOLOGY_NUMA_MODE_SMP or numa_mode == LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA );
  LFDS711_PAL_ASSERT( ms != NULL );
  LFDS711_PAL_ASSERT( numa_modes_list != NULL );

  lfds711_list_asu_init_valid_on_current_logical_core( numa_modes_list, NULL );

  switch( numa_mode )
  {
    case LIBBENCHMARK_TOPOLOGY_NUMA_MODE_SMP:
      tnn = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_topology_numa_node), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      tnn->mode = LIBBENCHMARK_TOPOLOGY_NUMA_MODE_SMP;
      LFDS711_LIST_ASU_SET_VALUE_IN_ELEMENT( tnn->lasue, tnn );
      lfds711_list_asu_insert_at_start( numa_modes_list, &tnn->lasue );
    break;

    case LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA:
      libbenchmark_topology_query( ts, LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMBER_OF_NODE_TYPE, (void *) (lfds711_pal_uint_t) LIBBENCHMARK_TOPOLOGY_NODE_TYPE_NUMA, &numa_node_count );

      if( numa_node_count == 1 )
      {
        tnn = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_topology_numa_node), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        tnn->mode = LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA;
        LFDS711_LIST_ASU_SET_VALUE_IN_ELEMENT( tnn->lasue, tnn );
        lfds711_list_asu_insert_at_start( numa_modes_list, &tnn->lasue );
      }

      if( numa_node_count >= 2 )
      {
        tnn = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_topology_numa_node), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        tnn->mode = LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA;
        LFDS711_LIST_ASU_SET_VALUE_IN_ELEMENT( tnn->lasue, tnn );
        lfds711_list_asu_insert_at_start( numa_modes_list, &tnn->lasue );

        tnn = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_topology_numa_node), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        tnn->mode = LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA_BUT_NOT_USED;
        LFDS711_LIST_ASU_SET_VALUE_IN_ELEMENT( tnn->lasue, tnn );
        lfds711_list_asu_insert_at_start( numa_modes_list, &tnn->lasue );
      }
    break;

    case LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA_BUT_NOT_USED:
      // TRD : not used
    break;
  }

  return;
}

