#------------------------------------------------------------------------------
# ECEN-5813 Summer 2017
# Project 2
#
# Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
# All Rights Reserved. (This work is unpublished)
#------------------------------------------------------------------------------
#
# @file source.mk
# @author Robert Blazewicz
# @author Vivek Sankaranarayanan
# @date July 15, 2017
# @brief This file contains list of source file for platform MKL.
#------------------------------------------------------------------------------
SRC = \
	src/memory.c		\
	src/conversion.c	\
	src/debug.c		\
	src/circbuf.c		\
	src/project1.c		\
	src/project2.c		\
	src/main.c		\
	src/startup_MKL25Z4.S	\
	src/uart.c		\
	src/system_MKL25Z4.c

LIB_FILES = \
	src/memory.c		\
	src/conversion.c	\
	src/debug.c		\
	src/circbuf.c
