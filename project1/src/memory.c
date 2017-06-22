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

#include <stdlib.h>
#include "memory.h"
#include "common_ccc.h"

/*---------------------------------------------------------------------------*/

uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length)
  {
  uint8_t *result;

  if (NULL == src || NULL == dst || length <= 0)
    {
    result = NULL;
    }
  else
    {
    for (uint8_t *ptr1 = src, *ptr2 = dst, *end = src + length; ptr1 < end; )
      {
      if(ptr1 != ptr2)
        *ptr2 = *ptr1;
      ptr2++;
      ptr1++;
      }
    result = dst;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
  {
  uint8_t *result;

  if (NULL == src || NULL == dst || length <= 0)
    {
    result = NULL;
    }
  else
    {
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

  if (NULL == src || length <= 0) 
    {
    result = NULL;
    } 
  else 
    {
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

  if (NULL == src || length <= 0)
    {
    result = NULL;
    }
  else
    {
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

  if (NULL == src || length <= 0) 
    {
    result = NULL;
    } 
  else 
    {
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

  if (length <= 0)
    {
    result = NULL;
    }
  else
    {
    const size_t malloc_bytes = length * sizeof(uint16_t);
    result = (int32_t*)malloc(malloc_bytes);
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

void free_words(uint32_t *src)
  {
  if (src != NULL)
    {
    free(src);
    }
  }
