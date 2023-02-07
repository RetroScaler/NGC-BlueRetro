##### paths #####
BINDIR := ../../bin
INCDIR := ../../inc
OBJDIR := ../../obj
SRCDIR := ../../src

##### misc #####
QUIETLY        := 1>/dev/null 2>/dev/null
VERSION_NUMBER := 1
MINOR_NUMBER   := 0
RELEASE_NUMBER := 0

##### sources, objects and libraries #####
BINNAME    := libbenchmark
ARFILENAME := $(BINNAME).a
ARPATHNAME := $(BINDIR)/$(ARFILENAME)
SOBASENAME := $(BINNAME).so
SONAME     := $(SOBASENAME).$(VERSION_NUMBER)
SOFILENAME := $(SONAME).$(MINOR_NUMBER).$(RELEASE_NUMBER)
SOPATHNAME := $(BINDIR)/$(SOFILENAME)
INCNAME    := $(INCDIR)/$(BINNAME).h
SRCDIRS    := libbenchmark_benchmarkinstance libbenchmark_benchmarks_btree_au_readn_writen libbenchmark_benchmarks_freelist_push1_then_pop1 libbenchmark_benchmarks_queue_umm_enqueue1_then_dequeue1 libbenchmark_benchmarkset libbenchmark_benchmarksuite libbenchmark_datastructures_btree_au libbenchmark_datastructures_freelist libbenchmark_datastructures_queue_umm libbenchmark_misc libbenchmark_porting_abstraction_layer libbenchmark_results libbenchmark_threadset libbenchmark_topology libbenchmark_topology_node
SOURCES    := libbenchmark_benchmarkinstance_cleanup.c libbenchmark_benchmarkinstance_init.c libbenchmark_benchmarkinstance_run.c \
              libbenchmark_benchmarks_btree_au_gcc_spinlock_atomic_readn_writen.c libbenchmark_benchmarks_btree_au_gcc_spinlock_sync_readn_writen.c libbenchmark_benchmarks_btree_au_liblfds700_lockfree_readn_writen.c libbenchmark_benchmarks_btree_au_liblfds711_lockfree_readn_writen.c libbenchmark_benchmarks_btree_au_msvc_spinlock_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_mutex_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_rwlock_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_spinlock_process_private_readn_writen.c libbenchmark_benchmarks_btree_au_pthread_spinlock_process_shared_readn_writen.c libbenchmark_benchmarks_btree_au_windows_critical_section_readn_writen.c libbenchmark_benchmarks_btree_au_windows_mutex_readn_writen.c \
              libbenchmark_benchmarks_freelist_gcc_spinlock_atomic_push1_then_pop1.c libbenchmark_benchmarks_freelist_gcc_spinlock_sync_push1_then_pop1.c libbenchmark_benchmarks_freelist_liblfds700_lockfree_push1_then_pop1.c libbenchmark_benchmarks_freelist_liblfds711_lockfree_push1_then_pop1.c libbenchmark_benchmarks_freelist_msvc_spinlock_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_mutex_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_rwlock_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_spinlock_process_private_push1_then_pop1.c libbenchmark_benchmarks_freelist_pthread_spinlock_process_shared_push1_then_pop1.c libbenchmark_benchmarks_freelist_windows_critical_section_push1_then_pop1.c libbenchmark_benchmarks_freelist_windows_mutex_push1_then_pop1.c \
              libbenchmark_benchmarks_queue_umm_gcc_spinlock_atomic_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_gcc_spinlock_sync_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_liblfds700_lockfree_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_liblfds711_lockfree_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_msvc_spinlock_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_mutex_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_rwlock_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_spinlock_process_private_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_pthread_spinlock_process_shared_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_windows_critical_section_enqueue1_dequeue1.c libbenchmark_benchmarks_queue_umm_windows_mutex_enqueue1_dequeue1.c \
              libbenchmark_benchmarkset_add.c libbenchmark_benchmarkset_cleanup.c libbenchmark_benchmarkset_gnuplot.c libbenchmark_benchmarkset_init.c libbenchmark_benchmarkset_run.c \
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
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
SYSLIBS    := 

##### default paths fix up #####
CPATH      := $(subst : ,:,$(SRCDIR):$(INCDIR))

##### tools #####
DG                     := gcc
DGFLAGS_MANDATORY      := -MM
DGFLAGS_OPTIONAL       := -std=gnu89

CC                     := gcc
CFLAGS_MANDATORY       := -c -fno-strict-aliasing
CFLAGS_OPTIONAL        := -std=gnu89 -Wall -Werror -Wno-unknown-pragmas
CFLAGS_MANDATORY_COV   := -O0 -ggdb -DCOVERAGE -fprofile-arcs -ftest-coverage
CFLAGS_MANDATORY_DBG   := -O0 -ggdb -D_DEBUG
CFLAGS_MANDATORY_PROF  := -O0 -ggdb -DPROF     -pg
CFLAGS_MANDATORY_REL   := -O2       -DNDEBUG
CFLAGS_MANDATORY_TSAN  := -O0 -ggdb -DTSAN     -fsanitize=thread -fPIC

AR                     := ar
ARFLAGS                :=
ARFLAGS_MANDATORY      := rcs
ARFLAGS_OPTIONAL       :=

LD                     := gcc
LDFLAGS_MANDATORY      := -shared -Wl,-soname,$(SONAME) -o $(SOPATHNAME)
LDFLAGS_OPTIONAL       := -std=gnu89 -Wall -Werror
LDFLAGS_MANDATORY_COV  := -O0 -fprofile-arcs -ftest-coverage
LDFLAGS_MANDATORY_DBG  := -O0 -ggdb
LDFLAGS_MANDATORY_PROF := -O0 -pg
LDFLAGS_MANDATORY_REL  := -O2 -s
LDFLAGS_MANDATORY_TSAN := -O0 -fsanitize=thread -fPIC

##### build variants #####
ifeq ($(findstring so,$(MAKECMDGOALS)),so)
  CFLAGS_MANDATORY += -fPIC
endif

# TRD : default to debug
ifeq ($(MAKECMDGOALS),)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_DBG)
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_DBG)
endif

ifeq ($(findstring cov,$(MAKECMDGOALS)),cov)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_COV)
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_COV)
  SYSLIBS += -lgcov
endif

ifeq ($(findstring dbg,$(MAKECMDGOALS)),dbg)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_DBG)
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_DBG)
endif

ifeq ($(findstring prof,$(MAKECMDGOALS)),prof)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_PROF)
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_PROF)
endif

ifeq ($(findstring rel,$(MAKECMDGOALS)),rel)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_REL)
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_REL)
endif

ifeq ($(findstring tsan,$(MAKECMDGOALS)),tsan)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_TSAN)
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_TSAN)
endif

##### search paths #####
vpath %.c $(patsubst %,$(SRCDIR)/%:,$(SRCDIRS))

##### implicit rules #####
$(OBJDIR)/%.o : %.c
	$(DG) $(DGFLAGS_OPTIONAL) $(DGFLAGS) $(DGFLAGS_MANDATORY) $< >$(OBJDIR)/$*.d
	$(CC) $(CFLAGS_OPTIONAL) $(CFLAGS) $(CFLAGS_MANDATORY) -o $@ $<

##### explicit rules #####
$(ARPATHNAME) : $(OBJECTS)
	$(AR) $(ARFLAGS_OPTIONAL) $(ARFLAGS) $(ARFLAGS_MANDATORY) $(ARPATHNAME) $(OBJECTS)

$(SOPATHNAME) : $(OBJECTS)
	$(LD) $(LDFLAGS_OPTIONAL) $(LDFLAGS) $(LDFLAGS_MANDATORY) $(OBJECTS) -o $(SOPATHNAME)
	@ln -fs $(SOFILENAME) $(BINDIR)/$(SONAME)
	@ln -fs $(SOFILENAME) $(BINDIR)/$(SOBASENAME)

##### phony #####
.PHONY : clean ar_cov ar_dbg ar_prof ar_rel ar_tsan ar_vanilla so_cov so_dbg so_prof so_rel so_tsan so_vanilla

clean : 
	@rm -f $(BINDIR)/* $(OBJDIR)/*

ar_cov       : $(ARPATHNAME) # archive (.a), coverage
ar_dbg       : $(ARPATHNAME) # archive (.a), debug
ar_prof      : $(ARPATHNAME) # archive (.a), profiling
ar_rel       : $(ARPATHNAME) # archive (.a), release
ar_tsan      : $(ARPATHNAME) # archive (.a), thread sanitizer
ar_vanilla   : $(ARPATHNAME) # archive (.a), no specific-build arguments
ar_install   :
  # TRD : leading backslash to use command rather than alias
  #       as many Linux distros have a built-in alias to force
  #       a prompt ("y/n?") on file overwrite - silent and
  #       unexpected interference which breaks a makefile
	@mkdir -p $(INSLIBDIR)
	@\cp $(ARPATHNAME) $(INSLIBDIR)
	@mkdir -p $(INSINCDIR)
	@\cp -r $(INCDIR)/* $(INSINCDIR)
ar_uninstall :
	@rm    $(INSLIBDIR)/$(ARFILENAME)
	@rm -r $(INSINCDIR)/$(BINNAME)
	@rm -r $(INSINCDIR)/$(BINNAME).h

so_cov       : $(SOPATHNAME) # shared (.so), coverage
so_dbg       : $(SOPATHNAME) # shared (.so), debug
so_prof      : $(SOPATHNAME) # shared (.so), profiling
so_rel       : $(SOPATHNAME) # shared (.so), release
so_tsan      : $(SOPATHNAME) # shared (.so), thread sanitizer
so_vanilla   : $(SOPATHNAME) # shared (.so), no specific-build arguments
so_install   : 
	@mkdir -p $(INSINCDIR)
	@\cp $(SOPATHNAME) $(INSLIBDIR)
	@ldconfig -vn $(INSLIBDIR)
	@ln -s $(SONAME) $(INSLIBDIR)/$(SOBASENAME)
	@mkdir -p $(INSLIBDIR)
	@\cp -r $(INCDIR)/* $(INSINCDIR)
so_uninstall : 
	@rm -f $(INSLIBDIR)/$(SOFILENAME)
	@rm -f $(INSLIBDIR)/$(SOBASENAME)
	@rm -f $(INSLIBDIR)/$(SONAME)
	@rm -r $(INSINCDIR)/$(BINNAME)
	@rm -r $(INSINCDIR)/$(BINNAME).h

##### dependencies #####
-include $(DEPENDS)

