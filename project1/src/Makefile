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
# as: make PLATFORM=CMSIS
PLATFORM=HOST

CFLAGS = -DPROJECT1 -DVERBOSE

RM= /bin/rm

#------------------------------------------------------------------------------
ifeq ($(PLATFORM),HOST)
	CC = gcc
	CFLAGS += -Wall -Werror -g -O0 -std=c99 -DPLATFORM_HOST
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
ifeq ($(PLATFORM),CMSIS)
	CC = arm-linux-gnueabi-gcc
#	CC = arm-linux-gnueabihf-gcc
	CFLAGS += -Wall -Werror -g -O0 -std=c99 -DPLATFORM_CMSIS
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
ifeq ($(PLATFORM),MLK)
	CC = arm-none-eabi-gcc
	CFLAGS = -Wall -Werror -g -O0 -std=c99 -DPLATFORM_MLK
	LDFLAGS = -Xlinker -Map=project1.map
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
		-I ../include/kl25z
endif

#------------------------------------------------------------------------------

OBJS	:= $(SRC:.c=.o)
PP	:= $(SRC:.c=.i)
DEP	:= $(SRC:.c=.d)
ASM	:= $(SRC:.c=.asm)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

%.i : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -E -o $@ $^

%.d : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -M -o $@ $^

%.asm : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -S -o $@ $^

$(BIN):	$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(BIN)

.PHONY: build
build: $(BIN)

.PHONY: all
all: $(BIN) $(PP) $(ASM) $(DEP)

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
