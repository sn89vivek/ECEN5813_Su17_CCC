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

#ifdef VERBOSE
void print_memory(uint8_t *start, uint32_t length)
  {
  if (start != NULL && length > 0) 
    {
    size_t ctr = 0;
    for (uint8_t *ptr = start, *end = start + length; ptr < end; ptr++)
      {
      /* Add a period between every 4 bytes */
      if ((0x00 == (ctr++ & 0x03)) && (ptr > start))
        {
        (void)fputc('.', stderr);
        }

      /* Convert each byte to hexadecimal and output to stderr */
      const int value1 = *ptr >> 4;
      const int value2 = *ptr & 0x0F;
      (void)fputc(value1 <= 9 ? '0' + value1 : 'A' + (value1-10), stderr);
      (void)fputc(value2 <= 9 ? '0' + value2 : 'A' + (value2-10), stderr);
      }
    }
  (void)fputc(CR, stderr);
  (void)fputc(LF, stderr);
  }
#endif
