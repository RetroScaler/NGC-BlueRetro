/***** defines *****/
#define LIBBENCHMARK_DATA_STRUCTURE_QUEUE_UMM_GCC_SPINLOCK_ATOMIC_GET_KEY_FROM_ELEMENT( queue_umm_element )             ( (queue_umm_element).key )
#define LIBBENCHMARK_DATA_STRUCTURE_QUEUE_UMM_GCC_SPINLOCK_ATOMIC_SET_KEY_IN_ELEMENT( queue_umm_element, new_key )      ( (queue_umm_element).key = (void *) (lfds711_pal_uint_t) (new_key) )
#define LIBBENCHMARK_DATA_STRUCTURE_QUEUE_UMM_GCC_SPINLOCK_ATOMIC_GET_VALUE_FROM_ELEMENT( queue_umm_element )           ( (queue_umm_element).value )
#define LIBBENCHMARK_DATA_STRUCTURE_QUEUE_UMM_GCC_SPINLOCK_ATOMIC_SET_VALUE_IN_ELEMENT( queue_umm_element, new_value )  ( (queue_umm_element).value = (void *) (lfds711_pal_uint_t) (new_value) )
#define LIBBENCHMARK_DATA_STRUCTURE_QUEUE_UMM_GCC_SPINLOCK_ATOMIC_GET_USER_STATE_FROM_STATE( queue_umm_state )          ( (queue_umm_state).user_state )

/***** structures *****/
struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element
{
  struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element
    *next;

  void
    *key,
    *value;
};

struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_state
{
  /* TRD : the pointers are on separate cache lines so threads enqueuing do not
           physically collide with thread dequeuing; this is done to be fair in
           the benchmark to the lock-free code, which does the same

           since we're not atomic, we don't need to be LFDS700_PAL_ATOMIC_ISOLATION_IN_BYTES
           bytes apart (e.g. the ERG on ARM), only cache line length in bytes
  */

  struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element LFDS711_PAL_ALIGN(LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES)
    *enqueue_umm,
    *dequeue_umm;

  pal_lock_gcc_spinlock_atomic_state LFDS711_PAL_ALIGN(LFDS711_PAL_ATOMIC_ISOLATION_IN_BYTES)
    lock_enqueue_umm,
    lock_dequeue_umm;

  void
    *user_state;
};

/***** public prototypes *****/
void libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_init( struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_state *qs, struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element *qe, void *user_state );
void libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_cleanup( struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_state *qs, void (*element_dequeue_umm_callback)(struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_state *qs, struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element *qe, enum flag dummy_flag) );

void libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_enqueue_umm( struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_state *qs, struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element *qe );
int libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_dequeue_umm( struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_state *qs, struct libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic_element **qe );

