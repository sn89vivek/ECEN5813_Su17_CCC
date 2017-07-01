/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file memory.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 19, 2017
 * @brief This file contains declaration of memory manipulation functions.
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

/*---------------------------------------------------------------------------*/

#include <stdint.h>

/**
 * @brief The function my_memmove() takes two byte pointers (one source and
 *        one destination) and a length of bytes to copy from the source
 *        location to the destination.
 *
 * @note This function does not handles overlap of src and dst. Will exit copy
 *       if src and dst overlap.
 *
 * @param  src - Source address
 * @param  dst - Destination address
 * @param  length - Number of bytes to copy
 *
 * @return NULL value indicates error condition
 * @return Pointer to the destination on success
 */
uint8_t * my_memmove(uint8_t *src, uint8_t *dst, size_t length);

/**
 * @brief The function my_memcpy() takes two byte pointers (one source and
 *        one destination) and a length of bytes to copy from the source
 *        location to the destination.
 *
 * @warning This function does not handle overlap of src and dst. Data can get
 *          corrupted if overlap detected.
 * @param  src - Source address
 * @param  dst - Destination address
 * @param  length - Number of bytes to copy
 *
 * @return NULL value indicates error condition
 * @return Pointer to the destination on success
 */
uint8_t * my_memcpy(uint8_t *src, uint8_t *dst, size_t length);

/**
 * @brief  The function my_memset() takes a pointer to a memory location, a
 *         length in bytes, a value and sets the memory to the specified value.
 *
 * @param  src - Source address of set operation
 * @param  length - Number of bytes to set
 * @param  value - Value to set the memory to
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t * my_memset(uint8_t *src, size_t length, uint8_t value);

/**
 * @brief The function my_memzero() takes a pointer to a memory location, a
 *        length in bytes and zeros out all of the memory.
 *
 * @param  src - Source address of set operation
 * @param  length - Number of bytes to zero out
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t * my_memzero(uint8_t *src, size_t length);

/**
 * @brief The function my_reverse() takes a pointer to a memory location, a
 *        length in bytes and reverses the bytes in the specified memory range.
 *
 * @param  src - Source address for the reverse operation
 * @param  length - Number of bytes to reverse
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t * my_reverse(uint8_t * src, size_t length);

/**
 * @brief The function reserve_words() takes a length of words to allocate in
 *        dynamic memory.
 *
 * @param  length - Number of words to allocate
 *
 * @return NULL value indicates error condition
 * @return Pointer to allocated memory
 */
int32_t * reserve_words(size_t length);

/**
 * @brief The function free_words() takes a length of words to allocate in
 *        dynamic memory.
 *
 * @param  src - Source address of allocated memory
 *
 * @return None
 */
void free_words(uint32_t * src);

/**
 * @brief The function find_smallest() scans a data array and returns the
 *        smallest value.
 *
 * @param  data - Source data
 * @param  length - Data length
 *
 * @return Smallest value
 */
uint8_t find_smallest(uint8_t *data, size_t length);

/*---------------------------------------------------------------------------*/

#endif /* __MEMORY_H__ */
