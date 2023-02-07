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
BINNAME    := libtest
LIB_BINARY := $(BINDIR)\$(BINNAME).lib
DLL_BINARY := $(BINDIR)\$(BINNAME).dll
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
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.obj,$(notdir $(SOURCES)))
SYSLIBS    := kernel32.lib
USRLIBS    := ..\..\..\..\liblfds711\bin\liblfds711.lib ..\..\..\libshared\bin\libshared.lib

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
	$(AR) $(ARFLAGS_OPTIONAL) $(ARFLAGS) $(ARFLAGS_MANDATORY) $(OBJECTS) /out:$(LIB_BINARY)

$(DLL_BINARY) : $(OBJECTS)
	$(LD) $(LDFLAGS_OPTIONAL) $(LDFLAGS) $(LDFLAGS_MANDATORY) $(CLIB) $(SYSLIBS) $(USRLIBS) $(OBJECTS) /out:$(DLL_BINARY)

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

