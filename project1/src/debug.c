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
 * @brief Defintions for debugging related functions.
 */

#include <stdio.h>
#include "debug.h"
#include "common_ccc.h"

/*---------------------------------------------------------------------------*/
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
void print_memory(uint8_t *start, uint32_t length)
  {
  const char8_t hex[16] =
    {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

  if (start != NULL && length > 0) 
    {
    size_t ctr = 0;
    for (uint8_t *ptr = start, *end = start + length; ptr < end; )
      {
      const int value1 = hex[*ptr >> 4];
      const int value2 = hex[*ptr & 0x0F];
      (void)fputc(value1, stderr);
      (void)fputc(value2, stderr);
      if (0x03 == (ctr++ & 0x03))
        {
        (void)fputc('.', stderr);
        }
      }
    }
  }
