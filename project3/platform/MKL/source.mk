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
# @brief This file contains list of source file for platform MKL.
#------------------------------------------------------------------------------
SRC = \
	src/board_kl25z.c	\
	src/circbuf.c		\
	src/conversion.c	\
	src/debug.c		\
	src/led_kl25z.c		\
	src/logger_kl25z.c	\
	src/logger_q.c		\
	src/main.c		\
	src/memory.c		\
	src/memory_dma.c	\
	src/nordic.c		\
	src/project1.c		\
	src/project2.c		\
	src/project3.c		\
	src/rtc_kl25z.c		\
	src/startup_MKL25Z4.S	\
	src/spi_kl25z.c		\
	src/system_MKL25Z4.c	\
	src/timer_kl25z.c	\
	src/uart0_kl25z.c

LIB_FILES = \
	src/circbuf.c		\
	src/conversion.c	\
	src/debug.c		\
	src/memory.c
