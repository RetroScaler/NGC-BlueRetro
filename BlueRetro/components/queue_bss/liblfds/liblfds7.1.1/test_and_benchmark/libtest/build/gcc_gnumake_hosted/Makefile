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
BINNAME    := libtest
ARFILENAME := $(BINNAME).a
ARPATHNAME := $(BINDIR)/$(ARFILENAME)
SOBASENAME := $(BINNAME).so
SONAME     := $(SOBASENAME).$(VERSION_NUMBER)
SOFILENAME := $(SONAME).$(MINOR_NUMBER).$(RELEASE_NUMBER)
SOPATHNAME := $(BINDIR)/$(SOFILENAME)
INCNAME    := $(INCDIR)/$(BINNAME).h
SRCDIRS    := libtest_misc libtest_porting_abstraction_layer libtest_results libtest_test libtest_tests libtest_testsuite libtest_threadset
SOURCES    := libtest_misc_determine_erg.c libtest_misc_globals.c libtest_misc_memory_helpers.c libtest_misc_pal_helpers.c libtest_misc_query.c \
              libtest_porting_abstraction_layer_free.c libtest_porting_abstraction_layer_get_full_logical_processor_set.c libtest_porting_abstraction_layer_malloc.c \
              libtest_results_cleanup.c libtest_results_get_result.c libtest_results_init.c libtest_results_put_result.c \
              libtest_test_cleanup.c libtest_test_init.c libtest_test_run.c \
              libtest_tests_btree_addonly_unbalanced_alignment.c libtest_tests_btree_addonly_unbalanced_random_adds_fail.c libtest_tests_btree_addonly_unbalanced_random_adds_fail_and_overwrite.c libtest_tests_btree_addonly_unbalanced_random_adds_overwrite.c \
              libtest_tests_freelist_alignment.c libtest_tests_freelist_ea_popping.c libtest_tests_freelist_ea_popping_and_pushing.c libtest_tests_freelist_ea_pushing.c libtest_tests_freelist_ea_rapid_popping_and_pushing.c libtest_tests_freelist_without_ea_popping.c libtest_tests_freelist_without_ea_popping_and_pushing.c libtest_tests_freelist_without_ea_pushing.c libtest_tests_freelist_without_ea_rapid_popping_and_pushing.c \
              libtest_tests_hash_addonly_alignment.c libtest_tests_hash_addonly_iterate.c libtest_tests_hash_addonly_random_adds_fail.c libtest_tests_hash_addonly_fail_and_overwrite.c libtest_tests_hash_addonly_random_adds_overwrite.c \
              libtest_tests_list_addonly_singlylinked_ordered_alignment.c libtest_tests_list_addonly_singlylinked_ordered_new_ordered.c libtest_tests_list_addonly_singlylinked_ordered_new_ordered_with_cursor.c \
              libtest_tests_list_addonly_singlylinked_unordered_alignment.c libtest_tests_list_addonly_singlylinked_unordered_new_after.c libtest_tests_list_addonly_singlylinked_unordered_new_end.c libtest_tests_list_addonly_singlylinked_unordered_new_start.c \
              libtest_tests_porting_abstraction_layer_atomic_add.c libtest_tests_porting_abstraction_layer_atomic_cas.c libtest_tests_porting_abstraction_layer_atomic_dwcas.c libtest_tests_porting_abstraction_layer_atomic_exchange.c \
              libtest_tests_prng_alignment.c libtest_tests_prng_generate.c \
              libtest_tests_queue_bounded_manyproducer_manyconsumer_alignment.c libtest_tests_queue_bounded_manyproducer_manyconsumer_count.c libtest_tests_queue_bounded_manyproducer_manyconsumer_enqueuing.c libtest_tests_queue_bounded_manyproducer_manyconsumer_dequeuing.c libtest_tests_queue_bounded_manyproducer_manyconsumer_enqueuing_and_dequeuing.c libtest_tests_queue_bounded_manyproducer_manyconsumer_rapid_enqueuing_and_dequeuing.c \
              libtest_tests_queue_bounded_singleproducer_singleconsumer_dequeuing.c libtest_tests_queue_bounded_singleproducer_singleconsumer_enqueuing.c libtest_tests_queue_bounded_singleproducer_singleconsumer_enqueuing_and_dequeuing.c \
              libtest_tests_queue_unbounded_manyproducer_manyconsumer_alignment.c libtest_tests_queue_unbounded_manyproducer_manyconsumer_dequeuing.c libtest_tests_queue_unbounded_manyproducer_manyconsumer_enqueuing.c libtest_tests_queue_unbounded_manyproducer_manyconsumer_enqueuing_and_dequeuing.c libtest_tests_queue_unbounded_manyproducer_manyconsumer_enqueuing_and_dequeuing_one_element.c libtest_tests_queue_unbounded_manyproducer_manyconsumer_rapid_enqueuing_and_dequeuing.c \
              libtest_tests_ringbuffer_reading.c libtest_tests_ringbuffer_reading_and_writing.c libtest_tests_ringbuffer_writing.c \
              libtest_tests_stack_alignment.c libtest_tests_stack_popping.c libtest_tests_stack_popping_and_pushing.c libtest_tests_stack_pushing.c libtest_tests_stack_rapid_popping_and_pushing.c \
              libtest_testsuite_cleanup.c libtest_testsuite_init.c libtest_testsuite_run.c \
              libtest_threadset_add.c libtest_threadset_cleanup.c libtest_threadset_init.c libtest_threadset_operations.c
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
SYSLIBS    := 

##### tools #####
DG                     := gcc
DGFLAGS_MANDATORY      := -MM
DGFLAGS_OPTIONAL       := -std=gnu89

CC                     := gcc
CFLAGS_MANDATORY       := -c -fno-strict-aliasing
CFLAGS_OPTIONAL        := -std=gnu89 -Wall -Werror -Wno-unknown-pragmas -Wno-uninitialized -Wno-unused-but-set-variable
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

