/***** includes *****/
#include "libshared_memory_internal.h"





/****************************************************************************/
void libshared_memory_init( struct libshared_memory_state *ms )
{
  LFDS711_PAL_ASSERT( ms != NULL );

  lfds711_list_asu_init_valid_on_current_logical_core( &ms->list_of_allocations, NULL );

  return;
}

