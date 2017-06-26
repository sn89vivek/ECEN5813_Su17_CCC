#------------------------------------------------------------------------------
# ECEN-5813 Summer 2017
# Project 1
#
# Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
# All Rights Reserved. (This work is unpublished)
#------------------------------------------------------------------------------
#
# @file memory.c
# @author Robert Blazewicz
# @author Vivek Sankaranarayanan
# @date June 24, 2017
# @brief This file contains build rules for the project.
#------------------------------------------------------------------------------

# The default platform is HOST for building locally on a Linux host.
# To override the default, define the platform on the make command like such
# as "make PLATFORM=MKL" or "make PLATFORM=BBB"
PLATFORM ?= HOST

CPPFLAGS += -DPROJECT1

ifdef VERBOSE
CPPFLAGS += -DVERBOSE
endif

RM = /bin/rm

LINT = splint
LINT_FLAGS = -posix-lib

OBJDUMP = objdump
OBJDUMP_FLAGS = -t

LIB_FILES = \
		  memory.c \
		  conversion.c \
		  debug.c
LIB_OBJS = $(LIB_FILES:.s=.o)
LIB_OUT = project1_lib.a
LIBGEN = ar
LIBFLAGS = -cr

#------------------------------------------------------------------------------
ifeq ($(PLATFORM),HOST)
	CC = gcc
	CFLAGS += -Wall -Werror -g -O0 -std=c99
	CPPFLAGS += -DPLATFORM_HOST
	LDFLAGS = -Xlinker -Map=project1.map
	BIN = project1.elf
	SRC = \
		memory.c		\
		conversion.c		\
		debug.c			\
		main.c			\
		project1.c
	INCLUDES = \
		-I ../include/common
endif

#------------------------------------------------------------------------------
ifeq ($(PLATFORM),MKL)
	CC = arm-none-eabi-gcc
	CFLAGS = -Wall -Werror -g -O0 -std=c99 \
		-mcpu=cortex-m0plus -mthumb -specs=nosys.specs
	CPPFLAGS += -DPLATFORM_MKL -DFORMAT_INT32_AS_LONG_INT
	LDFLAGS = -Xlinker -Map=project1.map \
		-L../platform -T MKL25Z128xxx4_flash.ld
	BIN = project1.elf
	SRC = \
		memory.c		\
		conversion.c		\
		debug.c			\
		main.c			\
		project1.c		\
		startup_MKL25Z4.S	\
		system_MKL25Z4.c
	INCLUDES = \
		-I ../include/common	\
		-I ../include/CMSIS	\
		-I ../include/kl25z
endif

#------------------------------------------------------------------------------
ifeq ($(PLATFORM),BBB)
#	CC = arm-linux-gnueabi-gcc
	CC = arm-linux-gnueabihf-gcc
	CFLAGS += -Wall -Werror -g -O0 -std=c99 \
		-mcpu=cortex-a8 -mthumb -march=armv7-a \
		-mfloat-abi=hard -mfpu=vfpv3-d16
	CPPFLAGS += -DPLATFORM_BBB
	LDFLAGS = -Xlinker -Map=project1.map
	BIN = project1.elf
	SRC = \
		memory.c		\
		conversion.c		\
		debug.c			\
		main.c			\
		project1.c
	INCLUDES = \
		-I ../include/common	\
		-I ../include/CMSIS
endif

#------------------------------------------------------------------------------

.PHONY: null
null:
	@echo "Usage: make [PLATFORM=<HOST|MKL|BBB>] [VERBOSE=1]"
	@echo "            [build|all|scratch|neat|clean|lint|objdump]"
	@echo "       make all"

OBJS	:= $(patsubst %.S,%.o,$(patsubst %.c,%.o,$(SRC)))
PP	:= $(SRC:.c=.i)
DEP	:= $(SRC:.c=.d)
ASM	:= $(SRC:.c=.asm)
LINT_FILES := $(SRC:.c=.lint)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c -o $@ $^

%.i : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -E -o $@ $^

%.d : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -M -o $@ $^

%.asm : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -S -o $@ $^

%.lint : %.c
	-$(LINT) $(LINT_FLAGS) $(CPPFLAGS) $(INCLUDES) $^

$(BIN):	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

.PHONY: build
build: $(BIN)

.PHONY: compile-all
compile-all: $(BIN)

.PHONY: all
all: build $(PP) $(ASM) $(DEP)

.PHONY:	scratch
scratch: clean build
	@true

.PHONY: neat
neat:
	@$(RM) -f *.o
	@$(RM) -f *.i
	@$(RM) -f *.d
	@$(RM) -f *.asm

.PHONY: clean
clean: neat
	@$(RM) -f *.map
	@$(RM) -f $(BIN)

.PHONY: lint
lint: $(LINT_FILES)
	@true

.PHONY: objdump
objdump:
	$(OBJDUMP) $(OBJDUMP_FLAGS) $(OBJS)

.PHONY: buildlib
buildlib: $(LIB_OBJS)
	$(LIBGEN) $(LIBFLAGS) $(LIB_OUT) $^


