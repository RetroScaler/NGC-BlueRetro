##### paths #####
BINDIR := ..\..\bin
OBJDIR := ..\..\obj
SRCDIR := ..\..\src

##### misc #####
QUIETLY := 1>nul 2>nul
NULL    := 
SPACE   := $(NULL) # TRD : necessary trailing space after the close bracket

##### sources, objects and libraries #####
BINNAME := test
BINARY  := $(BINDIR)/$(BINNAME).exe
SRCDIRS := .
SOURCES := main.c misc.c callbacks.c util_cmdline.c
OBJECTS := $(patsubst %.c,$(OBJDIR)/%.obj,$(notdir $(SOURCES)))
SYSLIBS := kernel32.lib
EXTLIBS := 
USRLIBS := ../../../../liblfds711/bin/liblfds711.lib ../../../../test_and_benchmark/libshared/bin/libshared.lib ../../../../test_and_benchmark/libtest/bin/libtest.lib

##### default paths fix up #####
INCLUDE += ;../../../../liblfds711/inc/;../../../../test_and_benchmark/libshared/inc/;../../../../test_and_benchmark/libtest/inc/;
LIB     += ;../../../../liblfds711/bin/;../../../../test_and_benchmark/libshared/inc/;../../../../test_and_benchmark/libtest/inc/;

##### tools #####
CC                     := cl
CFLAGS_MANDATORY       := 
CFLAGS_OPTIONAL        := /nologo /W4 /WX /c "/Fd$(BINDIR)\$(BINNAME).pdb" /DUNICODE /D_UNICODE /D_CRT_SECURE_NO_DEPRECATE /DWIN32_LEAN_AND_MEAN
CFLAGS_MANDATORY_DBG   := /Od /Gm /Zi /D_DEBUG
CFLAGS_MANDATORY_REL   := /Ox /DNDEBUG

LD                     := link
LDFLAGS_MANDATORY      := /nodefaultlib /subsystem:console
LDFLAGS_OPTIONAL       := /nologo /nxcompat /wx
LDFLAGS_MANDATORY_DBG  := /debug "/pdb:$(BINDIR)\$(BINNAME).pdb"
LDFLAGS_MANDATORY_REL  := /incremental:no

##### build variants #####
ifeq ($(MAKECMDGOALS),) # TRD : default to lib debug
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
vpath %.c $(patsubst %,$(SRCDIR)/%:,$(SRCDIRS))

##### implicit rules #####
$(OBJDIR)/%.obj : %.c
	$(CC) $(CFLAGS_OPTIONAL) $(CFLAGS) $(CFLAGS_MANDATORY) "/Fo$@" $<

##### explicit rules #####
$(BINARY) : $(OBJECTS)
	$(LD) $(LDFLAGS_OPTIONAL) $(LDFLAGS) $(LDFLAGS_MANDATORY) $(CLIB) $(SYSLIBS) $(EXTLIBS) $(USRLIBS) $(OBJECTS) /out:$(BINARY)

##### phony #####
.PHONY : clean librel libdbg dllrel dlldbg

clean : 
	@erase /Q $(OBJDIR)\*.obj $(OBJDIR)\*.res $(BINDIR)\$(BINNAME).* $(QUIETLY)

dlldbg : $(BINARY)
dllrel : $(BINARY)
libdbg : $(BINARY)
librel : $(BINARY)

##### dependencies #####
-include $(DEPENDS)

