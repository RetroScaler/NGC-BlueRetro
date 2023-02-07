/***** includes *****/
#include "libshared_ansi_internal.h"





/****************************************************************************/
lfds711_pal_uint_t libshared_ansi_strlen( char const * const string )
{
  char const
    *temp;

  LFDS711_PAL_ASSERT( string != NULL );

  temp = (char const *) string;

  while( *temp++ != '\0' );

  return (lfds711_pal_uint_t) (temp-1 - string);
}

