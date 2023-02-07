##### paths #####
BINDIR := ..\..\bin
INCDIR := ..\..\inc
OBJDIR := ..\..\obj
SRCDIR := ..\..\src

##### misc #####
QUIETLY := 1>nul 2>nul
NULL := 
SPACE := $(NULL) # TRD : with a trailing space

##### sources, objects and libraries #####
BINNAME    := libbenchmark
LIB_BINARY := $(BINDIR)\$(BINNAME).lib
DLL_BINARY := $(BINDIR)\$(BINNAME).dll
SRCDIRS    := libbenchmark_benchmarkinstance libbenchmark_benchmarks_btree_au_readn_writen libbenchmark_benchmarkset libbenchmark_benchmarks_freelist_push1_then_pop1 libbenchmark_benchmarks_queue_umm_enqueue1_then_dequeue1 libbenchmark_benchmarksuite libbenchmark_datastructures_btree_au libbenchmark_datastructures_freelist libbenchmark_datastructures_queue_umm libbenchmark_misc libbenchmark_porting_abstraction_layer libbenchmark_results libbenchmark_threadset libbenchmark_topology libbenchmark_topology_node
SOURCES    := libbenchmark_benchmarkinstance_cleanup.c libbenchmark_benchmarkinstance_init.c libbenchmark_benchmarkinstance_run.c \
              libbenchmark_benchmarkset_add.c libbenchmark_benchmarkset_cleanup.c libbenchmark_benchmarkset_gnuplot.c libbenchmark_benchmarkset_init.c libbenchmark_benchmarkset_run.c \
              libbenchmark_benchmarks_btree_au_gcc_spinlock_atomic_readn_writen.c libbenchmark_benchmarks_btree_au_gcc_spinlock_sync_readn_writen.c libbenchmark_benchmarks_btree_au_liblfds700_lockfree_readn_writen.c libbenchmark_benchmarks_btree_au_liblfds711_lockfree_readn_writen.c libbenchmark_benchmarks_btree_au_msvc_spinlock_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_mutex_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_rwlock_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_spinlock_process_private_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_spinlock_process_shared_readn_writen.c libbenchmark_benchmarks_btree_au_windows_critical_section_readn_writen.c libbenchmark_benchmarks_btree_au_windows_mutex_readn_writen.c \
              libbenchmark_benchmarks_freelist_gcc_spinlock_atomic_push1_then_pop1.c libbenchmark_benchmarks_freelist_gcc_spinlock_sync_push1_then_pop1.c libbenchmark_benchmarks_freelist_liblfds700_lockfree_push1_then_pop1.c libbenchmark_benchmarks_freelist_liblfds711_lockfree_push1_then_pop1.c libbenchmark_benchmarks_freelist_msvc_spinlock_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_mutex_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_rwlock_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_spinlock_process_private_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_spinlock_process_shared_push1_then_pop1.c libbenchmark_benchmarks_freelist_windows_critical_section_push1_then_pop1.c libbenchmark_benchmarks_freelist_windows_mutex_push1_then_pop1.c \
              libbenchmark_benchmarks_queue_umm_gcc_spinlock_atomic_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_gcc_spinlock_sync_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_liblfds700_lockfree_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_liblfds711_lockfree_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_msvc_spinlock_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_mutex_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_rwlock_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_spinlock_process_private_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_spinlock_process_shared_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_windows_critical_section_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_windows_mutex_enqueue1_dequeue1.c \
              libbenchmark_benchmarksuite_add.c libbenchmark_benchmarksuite_cleanup.c libbenchmark_benchmarksuite_gnuplot.c libbenchmark_benchmarksuite_init.c libbenchmark_benchmarksuite_run.c \
              libbenchmark_datastructure_btree_au_gcc_spinlock_atomic.c libbenchmark_datastructure_btree_au_gcc_spinlock_sync.c libbenchmark_datastructure_btree_au_msvc_spinlock.c libbenchmark_datastructure_btree_au_pthread_mutex.c libbenchmark_datastructure_btree_au_pthread_rwlock.c libbenchmark_datastructure_btree_au_pthread_spinlock_process_private.c libbenchmark_datastructure_btree_au_pthread_spinlock_process_shared.c libbenchmark_datastructure_btree_au_windows_critical_section.c libbenchmark_datastructure_btree_au_windows_mutex.c \
              libbenchmark_datastructure_freelist_gcc_spinlock_atomic.c libbenchmark_datastructure_freelist_gcc_spinlock_sync.c libbenchmark_datastructure_freelist_msvc_spinlock.c libbenchmark_datastructure_freelist_pthread_mutex.c libbenchmark_datastructure_freelist_pthread_rwlock.c libbenchmark_datastructure_freelist_pthread_spinlock_process_private.c libbenchmark_datastructure_freelist_pthread_spinlock_process_shared.c libbenchmark_datastructure_freelist_windows_critical_section.c libbenchmark_datastructure_freelist_windows_mutex.c \
              libbenchmark_datastructure_queue_umm_gcc_spinlock_atomic.c libbenchmark_datastructure_queue_umm_gcc_spinlock_sync.c libbenchmark_datastructure_queue_umm_msvc_spinlock.c libbenchmark_datastructure_queue_umm_pthread_mutex.c libbenchmark_datastructure_queue_umm_pthread_rwlock.c libbenchmark_datastructure_queue_umm_pthread_spinlock_process_private.c libbenchmark_datastructure_queue_umm_pthread_spinlock_process_shared.c libbenchmark_datastructure_queue_umm_windows_critical_section.c libbenchmark_datastructure_queue_umm_windows_mutex.c \
              libbenchmark_misc_globals.c libbenchmark_misc_pal_helpers.c libbenchmark_misc_query.c \
              libbenchmark_porting_abstraction_layer_populate_topology.c libbenchmark_porting_abstraction_layer_print_string.c \
              libbenchmark_results_cleanup.c libbenchmark_results_compare.c libbenchmark_results_get_result.c libbenchmark_results_init.c libbenchmark_results_put_result.c \
              libbenchmark_threadset_cleanup.c libbenchmark_threadset_init.c libbenchmark_threadset_operations.c \
              libbenchmark_topology_cleanup.c libbenchmark_topology_compare.c libbenchmark_topology_init.c libbenchmark_topology_insert.c libbenchmark_topology_iterate.c libbenchmark_topology_lpsets.c libbenchmark_topology_numa.c libbenchmark_topology_query.c libbenchmark_topology_string.c \
              libbenchmark_topology_node_cleanup.c libbenchmark_topology_node_compare.c libbenchmark_topology_node_init.c
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.obj,$(notdir $(SOURCES)))
SYSLIBS    := kernel32.lib
USRLIBS    := ..\..\..\..\..\liblfds7.0.0\liblfds700\bin\liblfds700.lib ..\..\..\..\liblfds711\bin\liblfds711.lib ..\..\..\libshared\bin\libshared.lib

##### default paths fix up #####
INCDIRS := $(patsubst %,%;,$(INCDIR))
INCLUDE += $(subst $(SPACE),,$(INCDIRS))

##### tools #####
CC                    := cl
CFLAGS_MANDATORY      := /c "/Fd$(BINDIR)\$(BINNAME).pdb" /wd 4068
CFLAGS_OPTIONAL       := /DWIN32_LEAN_AND_MEAN /DUNICODE /D_UNICODE /nologo /W4 /WX
CFLAGS_MANDATORY_DBG  := /Od /Gm /Zi /D_DEBUG
CFLAGS_MANDATORY_REL  := /Ox /DNDEBUG

AR                    := lib
ARFLAGS               :=
ARFLAGS_MANDATORY     := /subsystem:console
ARFLAGS_OPTIONAL      := /nologo /wx /verbose

LD                    := link
LDFLAGS_MANDATORY     := /def:$(BINNAME).def /dll /nodefaultlib /subsystem:console
LDFLAGS_OPTIONAL      := /nologo /nxcompat /wx
LDFLAGS_MANDATORY_DBG := /debug "/pdb:$(BINDIR)\$(BINNAME).pdb"
LDFLAGS_MANDATORY_REL := /incremental:no

##### variants #####
ifeq ($(MAKECMDGOALS),) # TRD : default to debug lib
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_DBG) /MTd
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_DBG)
  CLIB              := libcmtd.lib
endif

ifeq ($(MAKECMDGOALS),libdbg)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_DBG) /MTd
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_DBG)
  CLIB              := libcmtd.lib
endif

ifeq ($(MAKECMDGOALS),librel)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_REL) /MT
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_REL)
  CLIB              := libcmt.lib
endif

ifeq ($(MAKECMDGOALS),dlldbg)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_DBG) /MDd
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_DBG)
  CLIB              := msvcrtd.lib
endif

ifeq ($(MAKECMDGOALS),dllrel)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_REL) /MD
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_REL)
  CLIB              := msvcrt.lib
endif

##### search paths #####
vpath %.c $(patsubst %,$(SRCDIR)/%;,$(SRCDIRS))

##### implicit rules #####
$(OBJDIR)/%.obj : %.c
	$(CC) $(CFLAGS_OPTIONAL) $(CFLAGS) $(CFLAGS_MANDATORY) "/Fo$@" $<

##### explicit rules #####
$(LIB_BINARY) : $(OBJECTS)
	$(AR) $(ARFLAGS_OPTIONAL) $(AFLAGS) $(ARFLAGS_MANDATORY) $(OBJECTS) /out:$(LIB_BINARY)

$(DLL_BINARY) : $(OBJECTS)
	$(LD) $(LDFLAGS_OPTIONAL) $(LFLAGS) $(LDFLAGS_MANDATORY) $(CLIB) $(SYSLIBS) $(USRLIBS) $(OBJECTS) /out:$(DLL_BINARY)

##### phony #####
.PHONY : clean librel libdbg dllrel dlldbg

clean : 
	@erase /Q $(BINDIR)\$(BINNAME).* $(OBJDIR)\*.obj $(QUIETLY)

dllrel : $(DLL_BINARY)
dlldbg : $(DLL_BINARY)

librel : $(LIB_BINARY)
libdbg : $(LIB_BINARY)

##### notes #####
# /wd 4068 : turn off "unknown pragma" warning

