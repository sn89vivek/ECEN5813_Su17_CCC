#------------------------------------------------------------------------------
# ECEN-5813 Summer 2017
# Project 3
#
# Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
# All Rights Reserved. (This work is unpublished)
#------------------------------------------------------------------------------
#
# @file platform.mk
# @author Robert Blazewicz
# @author Vivek Sankaranarayanan
# @date July 15, 2017
# @brief This file contains build rules for platform BBB.
#------------------------------------------------------------------------------

LINT = splint
LINT_FLAGS = -posix-lib

OBJDUMP = objdump
OBJDUMP_FLAGS = -t

LIBDIR =
LIBS =

LIB_OBJS = $(LIB_FILES:.c=.o)
LIB_OUT = project3_lib.a
LIBGEN = ar
LIBFLAGS = -cr

#CC = arm-linux-gnueabi-gcc
CC = arm-linux-gnueabihf-gcc
CFLAGS += -Wall -Werror -g -O0 -std=c99 \
	-mcpu=cortex-a8 -mthumb -march=armv7-a \
	-mfloat-abi=hard -mfpu=vfpv3-d16
CPPFLAGS += -DPLATFORM_BBB
LDFLAGS = -Xlinker -Map=$(OBJDIR)/project3.map
BIN = project3.elf
INCLUDES = \
	-I include/common	\
	-I include/CMSIS
