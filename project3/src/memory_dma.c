/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file memory_dma.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 23, 2017
 * @brief This file contains definition of memory manipulation functions that
 *        utilize DMA controller for fast data transfers.
 */

#include "common_ccc.h"
#include "memory_dma.h"

/*---------------------------------------------------------------------------*/

uint8_t *memmove_dma(uint8_t *src, uint8_t *dst, size_t length)
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

uint8_t *memcpy_dma(uint8_t *src, uint8_t *dst, size_t length)
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

uint8_t *memset_dma(uint8_t *src, size_t length, uint8_t value)
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

uint8_t *memzero_dma(uint8_t *src, size_t length)
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
