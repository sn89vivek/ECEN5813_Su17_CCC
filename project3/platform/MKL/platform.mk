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
# @brief This file contains build rules for platform MKL.
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

CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -g -O0 -std=c99 \
	-mcpu=cortex-m0plus -mthumb -specs=nosys.specs
CPPFLAGS += -DPLATFORM_MKL -DFORMAT_INT32_AS_LONG_INT
LDFLAGS = -Xlinker -Map=$(OBJDIR)/project3.map \
	-Lplatform/MKL -T MKL25Z128xxx4_flash.ld
BIN = project3.elf
INCLUDES = \
	-I include/common	\
	-I include/CMSIS	\
	-I include/kl25z
