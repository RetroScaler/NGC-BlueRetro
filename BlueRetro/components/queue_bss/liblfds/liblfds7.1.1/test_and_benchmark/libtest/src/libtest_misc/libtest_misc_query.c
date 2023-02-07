/***** includes *****/
#include "libtest_misc_internal.h"





/****************************************************************************/
#pragma warning( disable : 4100 )

void libtest_misc_query( enum libtest_misc_query query_type, void *query_input, void *query_output )
{
  // TRD : query type can be any value in its range
  // TRD : query_input can be NULL in some cases
  // TRD : query_outputput can be NULL in some cases

  switch( query_type )
  {
    case LIBTEST_MISC_QUERY_GET_BUILD_AND_VERSION_STRING:
    {
      char static const
        * const build_and_version_string = "libtest " LIBTEST_MISC_VERSION_STRING " (" BUILD_TYPE_STRING ", " LIBTEST_PAL_OS_STRING ", " MODE_TYPE_STRING ")";

      LFDS711_PAL_ASSERT( query_input == NULL );
      LFDS711_PAL_ASSERT( query_output != NULL );

      *(char const **) query_output = build_and_version_string;
    }
    break;
  }

  return;
}

#pragma warning( default : 4100 )

