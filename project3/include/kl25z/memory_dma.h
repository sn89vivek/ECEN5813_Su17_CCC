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

typedef struct
  {
  uint32_t tf_size_in_bytes;
  uint32_t dma_done;
  } dma_config_t;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function memmove_dma() takes two byte pointers (one source and
 *        one destination) and a length of bytes to copy from the source
 *        location to the destination. Uses DMA for the transfer
 *
 * @note This function does handles overlap of src and dst.
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
 * @brief  The function my_memset() takes a pointer to a memory location, a
 *         length in bytes, a value and sets the memory to the specified value.
 *         Uses DMA for the transfer
 *
 * @param  src - Source address of set operation
 * @param  length - Number of bytes to zero out
 *
 * @return NULL value indicates error condition
 * @return Pointer to source
 */
uint8_t *memset_dma(uint8_t *src, size_t length, uint8_t value);

/**
 * @brief The function initializes DMA
 *
 * @param None
 * @return None
 */
void dma_board_init();

/**
 * @brief This function configures DMA.
 *
 * @param None
 * @return None
 */
void dma_configure();

/**
 * @brief The function tests and profiles all dma operations
 *
 * @param  None
 * @param  None
 *
 */
void dma_memory_tests();

/*---------------------------------------------------------------------------*/

INLINE void dma_block_wait(uint8_t ch)
  {
  while(DMA_DSR_BCR(ch) & DMA_DSR_BCR_BSY_MASK)
    {
    }
  }

/*---------------------------------------------------------------------------*/

INLINE void dma_start(uint8_t ch)
  {
  DMA_DCR(ch) |= DMA_DCR_START(1);
  }

INLINE uint8_t dma_width_calc(uint8_t wd)
  {
  if(wd == 4)
    return 0;
  if(wd == 1)
    return 1;
  if(wd == 2)
    return 2;
  return 3;
  }

#endif /* __MEMORY_DMA_H__ */
