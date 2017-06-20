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

/*---------------------------------------------------------------------------*/
/**
 * @brief The function my_memcpy() takes two byte pointers (one source and
 *        one destination) and a length of bytes to copy from the source
 *        location to the destination.
 *
 * @param  src - Source address
 * @param  dst - Destination address
 * @param  length - Number of bytes to copy
 *
 * @return NULL value indicates error condition
 * @return Pointer to the destination on success
 */
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst, size_t length)
{
  uint8_t *result;

  if (NULL == src || NULL == dst || length <= 0) {
    result = NULL;
  } else {
    for (uint8_t *ptr1 = src, *ptr2 = dst, *end = src + length; ptr1 < end; ) {
      *ptr2++ = *ptr1++;
    }
    result = dst;
  }

  return result;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief xxx
 *
 * @param  src - xxx
 * @param  length - xxx
 * @param  value - xxx
 *
 * @return NULL value indicates error condition
 * @return xxx
 */
int8_t *my_memset(uint8_t *src, size_t length, uint8_t value)
{
  return NULL;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief The function my_memzero() takes a pointer to a memory location, a
 *        length in bytes and zeros out all of the memory.
 *
 * @param  src - Source address of copy operation
 * @param  length - Number of bytes to zero out
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t *my_memzero(uint8_t *src, size_t length)
{
  uint8_t *result;

  if (NULL == src || length <= 0) {
    result = NULL;
  } else {
    for (uint8_t *ptr1 = src, *end = src + length; ptr1 < end; ) {
      *ptr1++ = 0x00;
    }
    result = src;
  }

  return result;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief xxx
 *
 * @param  src - xxx
 * @param  length - xxx
 *
 * @return NULL value indicates error condition
 * @return xxx
 */
uint8_t *my_reverse(uint8_t *src, size_t length)
{
  return NULL;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief The function reserve_words() takes a length of words to allocate in
 *        dynamic memory.
 *
 * @param  length - Number of words to allocate
 *
 * @return NULL value indicates error condition
 * @return Pointer to allocated memory
 */
int32_t *reserve_words(size_t length)
{
  uint8_t *result;

  if (length <= 0) {
    result = NULL;
  } else {
    const size_t malloc_bytes = length * sizeof(unit16_t);
    result = (uint32_t*)malloc(malloc_bytes);
  }

  return result;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief xxx
 *
 * @param  src - xxx
 *
 * @return xxx
 */
void free_words(uint32_t *src)
{

}
