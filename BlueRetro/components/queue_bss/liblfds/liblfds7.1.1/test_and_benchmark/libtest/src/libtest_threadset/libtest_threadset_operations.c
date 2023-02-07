/***** includes *****/
#include "libtest_threadset_internal.h"





/****************************************************************************/
void libtest_threadset_run( struct libtest_threadset_state *ts )
{
  struct lfds711_list_asu_element
    *lasue = NULL;

  struct libtest_threadset_per_thread_state
    *pts;

  LFDS711_PAL_ASSERT( ts != NULL );

  LFDS711_MISC_BARRIER_STORE;

  lfds711_misc_force_store();

  while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(ts->list_of_per_thread_states,lasue) )
  {
    pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
    libshared_pal_thread_start( &pts->thread_handle, &pts->pti );
  }

  ts->threadset_start_flag = RAISED;

  LFDS711_PAL_ASSERT( ts != NULL );

  while( LFDS711_LIST_ASU_GET_START_AND_THEN_NEXT(ts->list_of_per_thread_states,lasue) )
  {
    pts = LFDS711_LIST_ASU_GET_VALUE_FROM_ELEMENT( *lasue );
    libshared_pal_thread_wait( pts->thread_handle );
  }

  return;
}





/****************************************************************************/
void libtest_threadset_thread_ready_and_wait( struct libtest_threadset_per_thread_state *pts )
{
  LFDS711_PAL_ASSERT( pts != NULL );

  pts->thread_ready_flag = RAISED;

  LFDS711_MISC_BARRIER_FULL;

  while( *pts->threadset_start_flag == LOWERED )
    LFDS711_MISC_BARRIER_LOAD;

  return;
}

