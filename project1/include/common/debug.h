/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file debug.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 19, 2017
 * @brief Declarations for debugging related functions.
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*---------------------------------------------------------------------------*/

#include <stdint.h>

/**
 * @brief The function print_memory() takes a pointer to memory and prints the
 *        hex output of bytes given a pointer to a memory location and a length
 *        of bytes to print.
 *
 * @param  src - Start address of memory
 * @param  length - Number of bytes to print
 *
 * @return None
 */
void print_memory(uint8_t *start, uint32_t length);

/*---------------------------------------------------------------------------*/

#endif /* __DEBUG_H__ */
