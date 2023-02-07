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
BINNAME    := libshared
LIB_BINARY := $(BINDIR)\$(BINNAME).lib
DLL_BINARY := $(BINDIR)\$(BINNAME).dll
SRCDIRS    := libshared_ansi libshared_memory libshared_misc libshared_porting_abstraction_layer
SOURCES    := libshared_ansi_strcat.c libshared_ansi_strcat_char.c libshared_ansi_strcat_number.c libshared_ansi_strcpy.c libshared_ansi_strlen.c \
              libshared_memory_add.c libshared_memory_alloc.c libshared_memory_cleanup.c libshared_memory_init.c libshared_memory_query.c libshared_memory_rollback.c \
              libshared_misc_query.c \
              libshared_porting_abstraction_layer_thread_start.c libshared_porting_abstraction_layer_thread_wait.c
OBJECTS    := $(patsubst %.c,$(OBJDIR)/%.obj,$(notdir $(SOURCES)))
SYSLIBS    := kernel32.lib
USRLIBS    := ..\..\..\..\liblfds711\bin\liblfds711.lib

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
  CLIB              := msvcrtd.lib
endif

ifeq ($(MAKECMDGOALS),librel)
  CFLAGS_MANDATORY  += $(CFLAGS_MANDATORY_REL) /MT
  LDFLAGS_MANDATORY += $(LDFLAGS_MANDATORY_REL)
  CLIB              := msvcrt.lib
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

