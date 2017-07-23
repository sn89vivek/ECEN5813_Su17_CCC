/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file memory_dma.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 23, 2017
 * @brief This file contains declaration of memory manipulation functions that
 *        utilize DMA controller for fast data transfers.
 */

#ifndef __MEMORY_DMA_H__
#define __MEMORY_DMA_H__

/*---------------------------------------------------------------------------*/

/**
 * @brief The function memmove_dma() takes two byte pointers (one source and
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
uint8_t * memmove_dma(uint8_t *src, uint8_t *dst, size_t length);

/**
 * @brief The function memcpy_dma() takes two byte pointers (one source and
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
uint8_t * memcpy_dma(uint8_t *src, uint8_t *dst, size_t length);

/**
 * @brief  The function memset_dma() takes a pointer to a memory location, a
 *         length in bytes, a value and sets the memory to the specified value.
 *
 * @param  src - Source address of set operation
 * @param  length - Number of bytes to set
 * @param  value - Value to set the memory to
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t * memset_dma(uint8_t *src, size_t length, uint8_t value);

/**
 * @brief The function memzero_dma() takes a pointer to a memory location, a
 *        length in bytes and zeros out all of the memory.
 *
 * @param  src - Source address of set operation
 * @param  length - Number of bytes to zero out
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t * memzero_dma(uint8_t *src, size_t length);

/*---------------------------------------------------------------------------*/

#endif /* __MEMORY_DMA_H__ */
