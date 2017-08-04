#------------------------------------------------------------------------------
# ECEN-5813 Summer 2017
# Project 3
#
# Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
# All Rights Reserved. (This work is unpublished)
#------------------------------------------------------------------------------
#
# @file Makefile
# @author Robert Blazewicz
# @author Vivek Sankaranarayanan
# @date June 24, 2017
# @brief This file contains build rules for the project.
#------------------------------------------------------------------------------

# The default platform is HOST for building locally on a Linux host.
# To override the default, define the platform on the make command like such
# as "make PLATFORM=MKL" or "make PLATFORM=BBB"
PLATFORM ?= HOST

ifdef PROJECT1
CPPFLAGS += -DPROJECT1
endif
ifdef PROJECT2
CPPFLAGS += -DPROJECT2
endif
ifdef PROJECT3
CPPFLAGS += -DPROJECT3
endif

ifdef VERBOSE
CPPFLAGS += -DVERBOSE
endif

MKDIR = /bin/mkdir
RM = /bin/rm

include platform/$(PLATFORM)/platform.mk
include platform/$(PLATFORM)/source.mk

SRCDIR = src
UTEST_DIR = test

OBJDIR = Debug_$(PLATFORM)
#OBJDIR = Release_$(PLATFORM)

#------------------------------------------------------------------------------

.PHONY: null
null:
	@echo "Usage: make [PLATFORM=<HOST|MKL|BBB>] [VERBOSE=1]"
	@echo "            [build|all|scratch|neat|clean|lint|objdump|"
	@echo "             unittests]"
	@echo "       make all"

OBJS	:= $(patsubst $(SRCDIR)/%.S,$(OBJDIR)/%.o, \
	   $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC)))
PP	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.i,$(SRC))
DEP	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SRC))
ASM	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.asm,$(SRC))
LINTS	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.lint,$(SRC))

UTEST_OBJ := $(patsubst $(UTEST_DIR)/%.c,$(OBJDIR)/%.o,$(UTEST_SRC))
UTEST_EXE := $(patsubst $(OBJDIR)/%.o,$(OBJDIR)/%.elf,$(UTEST_OBJ))

$(OBJDIR)/%.o : $(UTEST_DIR)/%.c
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< $(LIBDIR) $(LIBS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< $(LIBDIR) $(LIBS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.S
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< $(LIBDIR) $(LIBS) -o $@

$(OBJDIR)/%.i : $(SRCDIR)/%.c
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -E $< -o $@

$(OBJDIR)/%.d : $(SRCDIR)/%.c
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -M $< -o $@

$(OBJDIR)/%.asm : $(SRCDIR)/%.c
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -S $< -o $@

$(OBJDIR)/%.lint : $(SRCDIR)/%.c
	@$(MKDIR) -p $(OBJDIR)
	-$(LINT) $(LINT_FLAGS) $(CPPFLAGS) $(INCLUDES) $^

$(OBJDIR)/$(BIN) : $(OBJS)
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

.PHONY: build
build: $(OBJDIR)/$(BIN)

.PHONY: compile-all
compile-all: $(OBJDIR)/$(BIN)

.PHONY: all
all: build $(PP) $(ASM) $(DEP)

.PHONY:	scratch
scratch: clean build
	@true

.PHONY: neat
neat:
	@$(RM) -f $(OBJDIR)/*.o
	@$(RM) -f $(OBJDIR)/*.i
	@$(RM) -f $(OBJDIR)/*.d
	@$(RM) -f $(OBJDIR)/*.asm

.PHONY: clean
clean: neat
	@$(RM) -f $(OBJDIR)/*.map
	@$(RM) -f $(OBJDIR)/*.elf

.PHONY: lint
lint: $(LINTS)
	@true

.PHONY: objdump
objdump: build
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(OBJS)

.PHONY: objdump2
objdump2: build
	$(OBJDUMP) -SD $(OBJDIR)/$(BIN)

.PHONY: buildlib
buildlib: $(LIB_OBJS)
	@$(MKDIR) -p $(OBJDIR)
	$(LIBGEN) $(LIBFLAGS) $(LIB_OUT) $^

#------------------------------------------------------------------------------

$(OBJDIR)/circbuf_test.elf : $(OBJDIR)/circbuf_test.o $(OBJDIR)/circbuf.o $(OBJDIR)/memory.o
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lcmocka -o $@

$(OBJDIR)/conversion_test.elf : $(OBJDIR)/conversion_test.o $(OBJDIR)/conversion.o
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lcmocka -o $@

$(OBJDIR)/memory_test.elf : $(OBJDIR)/memory_test.o $(OBJDIR)/memory.o
	@$(MKDIR) -p $(OBJDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lcmocka -o $@

.PHONY: unittests
unittests: CPPFLAGS += -DCMOCKA_UNIT_TESTS
unittests: $(UTEST_EXE)
	$(OBJDIR)/circbuf_test.elf
	$(OBJDIR)/conversion_test.elf
	$(OBJDIR)/memory_test.elf
