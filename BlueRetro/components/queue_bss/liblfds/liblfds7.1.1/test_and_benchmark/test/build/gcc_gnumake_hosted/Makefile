##### notes #####
# TRD : -fno-strict-aliasing is needed because GCC has messed up type punning and __may_alias__ does absolutely nothing
#       -Wno-unused-but-set-variable and -Wno-uninitialized are needed because GCC seems confused by the atomic intrinsics
#       the code base for release has been compiled with those warnings enabled, to show any valid errors

##### paths #####
BINDIR     := ../../bin
OBJDIR     := ../../obj
SRCDIR     := ../../src
LIBINCDIRS := ../../../../liblfds711/inc/ ../../../libtest/inc/ ../../../libshared/inc/
LIBBINDIRS := ../../../../liblfds711/bin/ ../../../libtest/bin/ ../../../libshared/bin/

##### misc #####
QUIETLY    := 1>/dev/null 2>/dev/null
NULL       := 
SPACE      := $(NULL) # TRD : with a trailing space

##### sources, objects and libraries #####
BINNAME    := test
BINARY     := $(BINDIR)/$(BINNAME)
SRCDIRS    := .
SOURCES    := main.c misc.c callbacks.c util_cmdline.c
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
SYSLIBS    := -lm -lpthread -lrt
USRLIBS    := -ltest -lshared -llfds711
LIBINCDIRS := $(subst $(SPACE), -I,$(LIBINCDIRS))
LIBBINDIRS := $(subst $(SPACE), -L,$(LIBBINDIRS))

##### tools #####
DG                     := gcc
DGFLAGS_MANDATORY      := -MM
DGFLAGS_OPTIONAL       := 

CC                     := gcc
CFLAGS_MANDATORY       := -c -pthread -I$(LIBINCDIRS)
CFLAGS_OPTIONAL        := -Wall -Werror -Wno-unknown-pragmas
CFLAGS_MANDATORY_COV   := -O0 -ggdb -DCOVERAGE -fprofile-arcs -ftest-coverage
CFLAGS_MANDATORY_DBG   := -O0 -ggdb -D_DEBUG
CFLAGS_MANDATORY_PROF  := -O0 -ggdb -DPROF     -pg
CFLAGS_MANDATORY_REL   := -O2       -DNDEBUG
CFLAGS_MANDATORY_TSAN  := -O0 -ggdb -DTSAN     -fsanitize=thread -fPIC

LD                     := gcc
LDFLAGS_MANDATORY      := -pthread -L$(LIBBINDIRS)
LDFLAGS_OPTIONAL       := -Wall -Werror
LDFLAGS_MANDATORY_COV  := -O0 -fprofile-arcs -ftest-coverage
LDFLAGS_MANDATORY_DBG  := -O0 -ggdb
LDFLAGS_MANDATORY_PROF := -O0 -pg
LDFLAGS_MANDATORY_REL  := -O2 -s
LDFLAGS_MANDATORY_TSAN := -O0 -fsanitize=thread -pie

##### build variants #####
ifeq ($(MAKECMDGOALS),) # TRD : default to debug
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
$(BINARY) : $(OBJECTS)
	$(LD) -o $(BINARY) $(LDFLAGS_OPTIONAL) $(LDFLAGS) $(LDFLAGS_MANDATORY) $(OBJECTS) $(USRLIBS) $(SYSLIBS)
	chmod +x $(BINARY)

##### phony #####
.PHONY : clean cov dbg prof rel tsan vanilla

clean : 
	@rm -f $(BINDIR)/$(BINNAME) $(OBJDIR)/*.o $(OBJDIR)/*.d $(OBJDIR)/*.gcda $(OBJDIR)/*.gcno

cov     : $(BINARY)
dbg     : $(BINARY)
prof    : $(BINARY)
rel     : $(BINARY)
tsan    : $(BINARY)
vanilla : $(BINARY)

##### dependencies #####
-include $(DEPENDS)

