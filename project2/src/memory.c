/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file memory.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 19, 2017
 * @brief This file contains definition of memory manipulation functions.
 */

#include "common_ccc.h"
#include "memory.h"

/*---------------------------------------------------------------------------*/

uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length)
  {
  uint8_t *result;

  if (NULL == src || NULL == dst || 0 == length)
    {
    result = NULL;
    }
  else
    {
    /* If the start of source lower in memory than the destination? */
    if (src < dst)
      /* Start of source is lower in memory than the destination. */
      {
      for (uint8_t *ptr1 = src + length - 1, *ptr2 = dst + length - 1;
           src <= ptr1; )
        {
        *ptr2-- = *ptr1--;
        }
      }
    else
      /* Start of destination is at or lower than the source in memory. */
      {
      for (uint8_t *ptr1 = src, *ptr2 = dst, *end = src + length; ptr1 < end; )
        {
        *ptr2++ = *ptr1++;
        }
      }
    result = dst;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
  {
  uint8_t *result;

  if (NULL == src || NULL == dst || 0 == length)
    {
    result = NULL;
    }
  else
    {
    /* Copy bytes from source to destination */
    for (uint8_t *ptr1 = src, *ptr2 = dst, *end = src + length; ptr1 < end; )
      {
      *ptr2++ = *ptr1++;
      }
    result = dst;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value)
  {
  uint8_t *result;

  if (NULL == src || 0 == length)
    {
    result = NULL;
    } 
  else 
    {
    /* Set target with value from source for length bytes */
    for (uint8_t *ptr = src, *end = src + length; ptr < end; )
      {
      *ptr++ = value;
      }
    result = src;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

uint8_t *my_memzero(uint8_t *src, size_t length)
  {
  uint8_t *result;

  if (NULL == src || 0 == length)
    {
    result = NULL;
    }
  else
    {
    /* Set target with zero from source for length bytes */
    for (uint8_t *ptr = src, *end = src + length; ptr < end; )
      {
      *ptr++ = 0x00;
      }
    result = src;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

uint8_t *my_reverse(uint8_t *src, size_t length)
  {
  uint8_t *result;
  uint8_t  swap;

  if (NULL == src || 0 == length)
    {
    result = NULL;
    } 
  else 
    {
    /* Reverse bytes in memory from source for length bytes */
    for (uint8_t *ptr = src, *end = src + (length - 1); ptr < end; )
      {
      swap = *ptr;
      *ptr++ = *end;
      *end-- = swap;
      }
    result = src;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

int32_t *reserve_words(size_t length)
  {
  int32_t *result;

  if (0 == length)
    {
    result = NULL;
    }
  else
    {
    /* Allocate a block of memory of length Words */
    const size_t malloc_bytes = length * sizeof(uint32_t);
    result = (int32_t*)malloc(malloc_bytes);
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

void free_words(uint32_t *src)
  {
  if (src != NULL)
    {
    /* Deallocate a block of memory */
    free(src);
    }
  }

/*---------------------------------------------------------------------------*/

uint8_t find_smallest(uint8_t *data, size_t length)
  {
  uint8_t smallest = 0xFF;

  if (data != NULL && 0 != length)
    {
    /* Search memory for lowest byte value */
    for (uint8_t *ptr = data, *end = data + length - 1; ptr < end; ptr++)
      {
      if (*ptr < smallest)
        smallest = *ptr;
      }
    }

  return smallest;
  }
