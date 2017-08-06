#------------------------------------------------------------------------------
# ECEN-5813 Summer 2017
# Project 3
#
# Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
# All Rights Reserved. (This work is unpublished)
#------------------------------------------------------------------------------
#
# @file source.mk
# @author Robert Blazewicz
# @author Vivek Sankaranarayanan
# @date July 15, 2017
# @brief This file contains source files for platform BBB.
#------------------------------------------------------------------------------
SRC = \
	src/board_bbb.c		\
	src/circbuf.c		\
	src/conversion.c	\
	src/debug.c		\
	src/logger.c		\
	src/logger_q.c		\
	src/memory.c		\
	src/project1.c		\
	src/project2.c		\
	src/project3.c		\
	src/main.c

LIB_FILES = \
	src/memory.c		\
	src/conversion.c	\
	src/debug.c		\
	src/circbuf.c
