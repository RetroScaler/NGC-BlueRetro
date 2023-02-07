/***** includes *****/
#include "libtest_tests_internal.h"





/****************************************************************************/
#pragma warning( disable : 4100 4127 ) // TRD : disables MSVC warning for condition expressions being const

void libtest_tests_prng_alignment( struct lfds711_list_asu_state *list_of_logical_processors, struct libshared_memory_state *ms, enum lfds711_misc_validity *dvs )
{
  LFDS711_PAL_ASSERT( list_of_logical_processors != NULL );
  LFDS711_PAL_ASSERT( ms != NULL );
  LFDS711_PAL_ASSERT( dvs != NULL );

  *dvs = LFDS711_MISC_VALIDITY_VALID;

  // TRD : struct lfds711_prng_state
  if( LIBTEST_MISC_OFFSETOF(struct lfds711_prng_state,entropy) % LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES != 0 )
    *dvs = LFDS711_MISC_VALIDITY_INVALID_TEST_DATA;

  return;
}

#pragma warning( default : 4100 4127 )

