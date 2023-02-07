/****************************************************************************/
#if( defined _MSC_VER && _MSC_VER >= 1400 )

  /* TRD : MSVC

           _MSC_VER  indicates Microsoft C compiler
                       - _InterlockedCompareExchangePointer requires 8.0 (1400)
  */

  /***** defines *****/
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK 1

  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_UNINITIALIZED  0
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_AVAILABLE      1
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_UNAVAILABLE    2

  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_CREATE( pal_lock_msvc_spinlock_state )  \
  {                                                                                   \
    pal_lock_msvc_spinlock_state = LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_AVAILABLE;     \
    LFDS711_MISC_BARRIER_STORE;                                                       \
    lfds711_misc_force_store();                                                       \
  }

  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_DESTROY( pal_lock_msvc_spinlock_state )  \
  {                                                                                    \
    pal_lock_msvc_spinlock_state = LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_UNAVAILABLE;    \
    LFDS711_MISC_BARRIER_STORE;                                                        \
    lfds711_misc_force_store();                                                        \
  }

  /* TRD : bloody MS - they have multiple functions for the same thing
          I have to use my own abstraction layer *just to get my code working on MS platforms!*
  */

  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_GET( pal_lock_msvc_spinlock_state )                                                                \
  {                                                                                                                                              \
    char unsigned                                                                                                                                \
      result;                                                                                                                                    \
                                                                                                                                                 \
    lfds711_pal_uint_t                                                                                                                           \
      compare;                                                                                                                                   \
                                                                                                                                                 \
    do                                                                                                                                           \
    {                                                                                                                                            \
      compare = LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_AVAILABLE;                                                                                                         \
      LFDS711_PAL_ATOMIC_CAS( &(pal_lock_msvc_spinlock_state), &compare, LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_UNAVAILABLE, LFDS711_MISC_CAS_STRENGTH_STRONG, result );  \
    }                                                                                                                                            \
    while( result == 0 );                                                                                                                        \
  }

  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_RELEASE( pal_lock_msvc_spinlock_state )  \
  {                                                                                    \
    LFDS711_PAL_ATOMIC_SET( &(pal_lock_msvc_spinlock_state), LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_AVAILABLE );         \
  }

  /***** typedefs *****/
  typedef lfds711_pal_uint_t pal_lock_msvc_spinlock_state;

#endif





/****************************************************************************/
#if( !defined LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK )

  /***** defines *****/
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK 0

  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_CREATE( pal_lock_msvc_spinlock_state )
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_DESTROY( pal_lock_msvc_spinlock_state )
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_GET( pal_lock_msvc_spinlock_state )
  #define LIBBENCHMARK_PAL_LOCK_MSVC_SPINLOCK_RELEASE( pal_lock_msvc_spinlock_state )

  /***** typedefs *****/
  typedef void * pal_lock_msvc_spinlock_state;

#endif

