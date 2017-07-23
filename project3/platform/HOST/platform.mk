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
# @brief This file contains build rules for platform HOST.
#------------------------------------------------------------------------------

LINT = splint
LINT_FLAGS =

OBJDUMP = objdump
OBJDUMP_FLAGS = -t

LIBDIR =
LIBS =

LIB_OBJS = $(LIB_FILES:.c=.o)
LIB_OUT = project3_lib.a
LIBGEN = ar
LIBFLAGS = -cr

CC = gcc
CFLAGS += -Wall -Werror -g -O0 -std=c99
CPPFLAGS += -DPLATFORM_HOST
LDFLAGS = -Xlinker -Map=$(OBJDIR)/project3.map
BIN = project3.elf
INCLUDES = \
	-I include/common
