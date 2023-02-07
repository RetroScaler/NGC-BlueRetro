/***** includes *****/
#include "libbenchmark_benchmarks_queue_umm_internal.h"

/***** structs *****/
struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state
{
  lfds711_pal_uint_t
    operation_count;
};





/****************************************************************************/
void libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_init( struct libbenchmark_topology_state *ts,
                                                                                       struct lfds711_list_aso_state *logical_processor_set,
                                                                                       struct libshared_memory_state *ms,
                                                                                       enum libbenchmark_topology_numa_mode numa_mode,
                                                                                       struct libbenchmark_threadset_state *tsets )
{
  lfds711_pal_uint_t
    loop,
    number_logical_processors,
    number_logical_processors_in_numa_node,
    largest_number_logical_processors_in_numa_node = 0;

  struct lfds711_list_asu_element
    *lasue = NULL,
    *lasue_lp = NULL;

  struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state
    *ptbs;

  struct libbenchmark_datastructure_queue_umm_windows_critical_section_element
    *qe;

  struct libbenchmark_datastructure_queue_umm_windows_critical_section_state
    *qs = NULL;

  struct libbenchmark_threadset_per_numa_state
    *pns,
    *largest_pns = NULL;

  struct libbenchmark_threadset_per_thread_state
    *pts;

  struct libbenchmark_topology_node_state
    *numa_node_for_lp;

  LFDS711_PAL_ASSERT( ts != NULL );
  LFDS711_PAL_ASSERT( logical_processor_set != NULL );
  LFDS711_PAL_ASSERT( ms != NULL );
  // TRD : numa_mode can be any value in its range
  LFDS711_PAL_ASSERT( tsets != NULL );

  libbenchmark_threadset_init( tsets, ts, logical_processor_set, ms, libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_thread, NULL );

  switch( numa_mode )
  {
    case LIBBENCHMARK_TOPOLOGY_NUMA_MODE_SMP:
      qs = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_state), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      lfds711_list_aso_query( logical_processor_set, LFDS711_LIST_ASO_QUERY_GET_POTENTIALLY_INACCURATE_COUNT, NULL, (void *) &number_logical_processors );
      qe = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_element) * (number_logical_processors+1), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      libbenchmark_datastructure_queue_umm_windows_critical_section_init( qs, &qe[0], NULL );
      for( loop = 1 ; loop < (number_logical_processors+1) ; loop++ )
        libbenchmark_datastructure_queue_umm_windows_critical_section_enqueue_umm( qs, &qe[loop] );
      // TRD : now the per-thread states
      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue) )
      {
        pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
        ptbs = libshared_memory_alloc_from_most_free_space_node( ms, sizeof(struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        pts->users_per_thread_state = ptbs;
      }
    break;

    case LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA:
      // TRD : get the NUMA node for the queue_umm state
      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_numa_states,lasue) )
      {
        pns = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );

        lasue_lp = NULL;
        number_logical_processors_in_numa_node = 0;

        while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue_lp) )
        {
          pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue_lp );

          libbenchmark_topology_query( ts, LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMA_NODE_FOR_LOGICAL_PROCESSOR, pts->tns_lp, &numa_node_for_lp );

          if( LIBBENCHMARK_TOPOLOGY_NODE_GET_NUMA_ID(*numa_node_for_lp) == pns->numa_node_id )
            number_logical_processors_in_numa_node++;
        }

        if( number_logical_processors_in_numa_node > largest_number_logical_processors_in_numa_node )
          largest_pns = pns;
      }

      qs = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_state), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      qe = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_element), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      libbenchmark_datastructure_queue_umm_windows_critical_section_init( qs, qe, NULL );

      /* TRD : for each NUMA node, alloc one element per thread in that NUMA node (from the current thread set)
               the dummy element comes from the same node as the queue_umm state and has already been done
      */

      lasue = NULL;

      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_numa_states,lasue) )
      {
        pns = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );

        /* TRD : for each NUMA node, figure out how many LPs in the current set are in that NUMA node
                 and allocate then the correct number of elements from this NUMA node (1 per LP)
        */

        lasue_lp = NULL;
        number_logical_processors_in_numa_node = 0;

        while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue_lp) )
        {
          pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue_lp );

          libbenchmark_topology_query( ts, LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMA_NODE_FOR_LOGICAL_PROCESSOR, pts->tns_lp, &numa_node_for_lp );

          if( LIBBENCHMARK_TOPOLOGY_NODE_GET_NUMA_ID(*numa_node_for_lp) == pns->numa_node_id )
            number_logical_processors_in_numa_node++;
        }

        qe = libshared_memory_alloc_from_specific_node( ms, pns->numa_node_id, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_element) * number_logical_processors_in_numa_node, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        for( loop = 0 ; loop < number_logical_processors_in_numa_node ; loop++ )
          libbenchmark_datastructure_queue_umm_windows_critical_section_enqueue_umm( qs, &qe[loop] );
      }

      // TRD : now the per-thread states

      lasue = NULL;

      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue) )
      {
        pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
        ptbs = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        pts->users_per_thread_state = ptbs;
      }
    break;

    case LIBBENCHMARK_TOPOLOGY_NUMA_MODE_NUMA_BUT_NOT_USED:
      lfds711_list_aso_query( logical_processor_set, LFDS711_LIST_ASO_QUERY_GET_POTENTIALLY_INACCURATE_COUNT, NULL, (void *) &number_logical_processors );

      // TRD : get the NUMA node for the queue_umm state
      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_numa_states,lasue) )
      {
        pns = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );

        lasue_lp = NULL;
        number_logical_processors_in_numa_node = 0;

        while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue_lp) )
        {
          pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue_lp );

          libbenchmark_topology_query( ts, LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMA_NODE_FOR_LOGICAL_PROCESSOR, pts->tns_lp, &numa_node_for_lp );

          if( LIBBENCHMARK_TOPOLOGY_NODE_GET_NUMA_ID(*numa_node_for_lp) == pns->numa_node_id )
            number_logical_processors_in_numa_node++;
        }

        if( number_logical_processors_in_numa_node > largest_number_logical_processors_in_numa_node )
          largest_pns = pns;
      }

      qs = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_state), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      qe = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_element) * (number_logical_processors+1), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
      libbenchmark_datastructure_queue_umm_windows_critical_section_init( qs, qe, NULL );

      /* TRD : for each NUMA node, alloc one element per thread in that NUMA node (from the current thread set)
               the dummy element comes from the same node as the queue_umm state and has already been done
      */

      lasue = NULL;

      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_numa_states,lasue) )
      {
        pns = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );

        /* TRD : for each NUMA node, figure out how many LPs in the current set are in that NUMA node
                 and allocate then the correct number of elements from this NUMA node (1 per LP)
        */

        lasue_lp = NULL;
        number_logical_processors_in_numa_node = 0;

        while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue_lp) )
        {
          pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue_lp );

          libbenchmark_topology_query( ts, LIBBENCHMARK_TOPOLOGY_QUERY_GET_NUMA_NODE_FOR_LOGICAL_PROCESSOR, pts->tns_lp, &numa_node_for_lp );

          if( LIBBENCHMARK_TOPOLOGY_NODE_GET_NUMA_ID(*numa_node_for_lp) == pns->numa_node_id )
            number_logical_processors_in_numa_node++;
        }

        // TRD : everything allocates from the queue_umm state NUMA node
        qe = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_datastructure_queue_umm_windows_critical_section_element) * number_logical_processors_in_numa_node, LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        for( loop = 0 ; loop < number_logical_processors_in_numa_node ; loop++ )
          libbenchmark_datastructure_queue_umm_windows_critical_section_enqueue_umm( qs, &qe[loop] );
      }

      // TRD : now the per-thread states

      lasue = NULL;

      while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue) )
      {
        pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
        ptbs = libshared_memory_alloc_from_specific_node( ms, largest_pns->numa_node_id, sizeof(struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state), LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES );
        pts->users_per_thread_state = ptbs;
      }    break;
  }

  tsets->users_threadset_state = qs;

  return;
}





/****************************************************************************/
libshared_pal_thread_return_t LIBSHARED_PAL_THREAD_CALLING_CONVENTION libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_thread( void *libbenchmark_threadset_per_thread_state )
{
  int long long unsigned
    current_time = 0,
    end_time,
    time_units_per_second;

  lfds711_pal_uint_t
    operation_count = 0,
    time_loop = 0;

  struct libbenchmark_datastructure_queue_umm_windows_critical_section_element
    *qe;

  struct libbenchmark_datastructure_queue_umm_windows_critical_section_state
    *qs;

  struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state
    *ptbs;

  struct libbenchmark_threadset_per_thread_state
    *pts;

  LFDS711_MISC_BARRIER_LOAD;

  LFDS711_PAL_ASSERT( libbenchmark_threadset_per_thread_state != NULL );

  pts = (struct libbenchmark_threadset_per_thread_state *) libbenchmark_threadset_per_thread_state;

  ptbs = LIBBENCHMARK_THREADSET_PER_THREAD_STATE_GET_USERS_PER_THREAD_STATE( *pts );
  qs = LIBBENCHMARK_THREADSET_PER_THREAD_STATE_GET_USERS_OVERALL_STATE( *pts );

  LIBBENCHMARK_PAL_TIME_UNITS_PER_SECOND( &time_units_per_second );

  libbenchmark_threadset_thread_ready_and_wait( pts );

  LIBBENCHMARK_PAL_GET_HIGHRES_TIME( &current_time );

  end_time = current_time + time_units_per_second * libbenchmark_globals_benchmark_duration_in_seconds;

  while( current_time < end_time )
  {
    libbenchmark_datastructure_queue_umm_windows_critical_section_dequeue_umm( qs, &qe );
    libbenchmark_datastructure_queue_umm_windows_critical_section_enqueue_umm( qs, qe );
    operation_count++;

    if( time_loop++ == TIME_LOOP_COUNT )
    {
      time_loop = 0;
      LIBBENCHMARK_PAL_GET_HIGHRES_TIME( &current_time );
    }
  }

  ptbs->operation_count = operation_count;

  LFDS711_MISC_BARRIER_STORE;

  lfds711_misc_force_store();

  return LIBSHARED_PAL_THREAD_RETURN_CAST(RETURN_SUCCESS);
}





/****************************************************************************/
void libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_cleanup( struct lfds711_list_aso_state *logical_processor_set,
                                                                                          enum libbenchmark_topology_numa_mode numa_mode,
                                                                                          struct libbenchmark_results_state *rs,
                                                                                          struct libbenchmark_threadset_state *tsets )
{
  struct libbenchmark_datastructure_queue_umm_windows_critical_section_state
    *qs;

  struct lfds711_list_asu_element
    *lasue = NULL;

  struct libbenchmark_benchmark_queue_umm_windows_critical_section_enqueue1_dequeue1_per_thread_benchmark_state
    *ptbs;

  struct libbenchmark_threadset_per_thread_state
    *pts;

  LFDS711_PAL_ASSERT( logical_processor_set != NULL );
  // TRD : numa_mode can be any value in its range
  LFDS711_PAL_ASSERT( rs != NULL );
  LFDS711_PAL_ASSERT( tsets != NULL );

  while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(tsets->list_of_per_thread_states,lasue) )
  {
    pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );

    ptbs = LIBBENCHMARK_THREADSET_PER_THREAD_STATE_GET_USERS_PER_THREAD_STATE( *pts );

    libbenchmark_results_put_result( rs,
                                     LIBBENCHMARK_DATASTRUCTURE_ID_QUEUE_UMM,
                                     LIBBENCHMARK_BENCHMARK_ID_ENQUEUE_UMM1_THEN_DEQUEUE_UMM1,
                                     LIBBENCHMARK_LOCK_ID_WINDOWS_CRITICAL_SECTION,
                                     numa_mode,
                                     logical_processor_set,
                                     LIBBENCHMARK_TOPOLOGY_NODE_GET_LOGICAL_PROCESSOR_NUMBER( *pts->tns_lp ),
                                     LIBBENCHMARK_TOPOLOGY_NODE_GET_WINDOWS_GROUP_NUMBER( *pts->tns_lp ),
                                     ptbs->operation_count );
  }

  qs = tsets->users_threadset_state;

  libbenchmark_datastructure_queue_umm_windows_critical_section_cleanup( qs, NULL );

  return;
}

