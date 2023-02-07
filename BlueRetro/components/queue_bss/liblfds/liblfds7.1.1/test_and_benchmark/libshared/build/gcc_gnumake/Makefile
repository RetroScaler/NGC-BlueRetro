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
BINNAME    := libshared
ARFILENAME := $(BINNAME).a
ARPATHNAME := $(BINDIR)/$(ARFILENAME)
SOBASENAME := $(BINNAME).so
SONAME     := $(SOBASENAME).$(VERSION_NUMBER)
SOFILENAME := $(SONAME).$(MINOR_NUMBER).$(RELEASE_NUMBER)
SOPATHNAME := $(BINDIR)/$(SOFILENAME)
INCNAME    := $(INCDIR)/$(BINNAME).h
SRCDIRS    := libshared_ansi libshared_memory libshared_misc libshared_porting_abstraction_layer
SOURCES    := libshared_ansi_strcat.c libshared_ansi_strcat_char.c libshared_ansi_strcat_number.c libshared_ansi_strcpy.c libshared_ansi_strlen.c \
              libshared_memory_add.c libshared_memory_alloc.c libshared_memory_cleanup.c libshared_memory_init.c libshared_memory_query.c libshared_memory_rollback.c \
              libshared_misc_query.c \
              libshared_porting_abstraction_layer_thread_start.c libshared_porting_abstraction_layer_thread_wait.c
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
SYSLIBS    := 

##### tools #####
DG                     := gcc
DGFLAGS_MANDATORY      := -MM
DGFLAGS_OPTIONAL       := -std=gnu89

CC                     := gcc
CFLAGS_MANDATORY       := -c
CFLAGS_OPTIONAL        := -ffreestanding -std=gnu89 -Wall -Werror -Wno-unknown-pragmas
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
LDFLAGS_OPTIONAL       := -nodefaultlibs -nostdlib -std=gnu89 -Wall -Werror
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
.PHONY : clean ar_cov ar_dbg ar_prof ar_rel ar_tsan ar_vanilla so_dbg so_prof so_rel so_tsan so_vanilla

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

# TRD : so_cov currently disabled as it cannot work with -nostdlib -nodefaultlibs
# so_cov       : $(SOPATHNAME) # shared (.so), coverage
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

