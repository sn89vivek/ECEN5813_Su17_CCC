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
#include "memory.h"
#include "memory_dma.h"

/*---------------------------------------------------------------------------*/

#define ENABLE_CLK                  1
#define ENABLE_DMA_INT              1
#define DMA_AUTO_ALIGN              1
#define DMA_DEST_INC                1

/*---------------------------------------------------------------------------*/

static uint8_t dma_transfer_width;

/*---------------------------------------------------------------------------*/

void DMA0_IRQHandler();
void dma_config(uint8_t ch, uint32_t src, uint32_t dest, uint8_t src_tf_wd,
                uint8_t dest_tf_wd, uint32_t sinc, uint8_t dinc,
                uint32_t length);
void buf_verify(uint8_t *buf, uint32_t length, uint8_t val);

/*---------------------------------------------------------------------------*/

uint8_t *memmove_dma(uint8_t *src, uint8_t *dst, size_t length)
  {
  uint8_t *result;
  size_t overlap = 0;

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
      if (src + length > dst)
        {
        overlap = src + length - dst;
        }
      }
    /* We don't care about overlap if src > dst */

    /* first pass transfer of non-overlapping bytes*/
  dma_block_wait(0);
  dma_config(0, (uint32_t)(src + overlap), (uint32_t)(dst + overlap),
             dma_transfer_width, 1,
             1, 1, length-overlap);
  dma_start(0);
  dma_block_wait(0);

  if(overlap != 0)
    {
    /* Second pass transfer of overlapping bytes */
    dma_block_wait(0);
    dma_config(0, (uint32_t)src, (uint32_t)dst,
               dma_transfer_width, 1,
               1, 1, overlap);
    dma_start(0);
    dma_block_wait(0);
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
    dma_block_wait(0);
    dma_config(0, (uint32_t)&value, (uint32_t)src, 1, dma_transfer_width,
               0, 1, length);
    dma_start(0);
    result = src;
    dma_block_wait(0);
    }
  return result;
  }

/*---------------------------------------------------------------------------*/

void dma_board_init()
  {
  SIM->SCGC6 |= SIM_SCGC6_DMAMUX(ENABLE_CLK);
  SIM->SCGC7 = SIM_SCGC7_DMA(ENABLE_CLK);
  }

/*---------------------------------------------------------------------------*/

void dma_configure()
  {
  /* Enable DMA0 interrupts and set priority at NVIC level */
  NVIC_EnableIRQ(DMA0_IRQn);
  NVIC_SetPriority(DMA0_IRQn, 0);
  }

/*---------------------------------------------------------------------------*/

void dma_memory_tests()
  {
  uint8_t *sbuf, *dbuf;
  sbuf = (uint8_t *)reserve_words(LENGTH_IN_WORDS(5000));
  dbuf = (uint8_t *)reserve_words(LENGTH_IN_WORDS(5000));
  if((dbuf != NULL) && (sbuf != NULL))
    {
    /* SET TESTS */
    /* 1-byte set tests */
    dma_transfer_width = 1;
    memset_dma(sbuf, 10, 0xA5);
    buf_verify(sbuf, 10, 0xA5);
    memset_dma(sbuf, 100, 0x5A);
    buf_verify(sbuf, 100, 0x5A);
    memset_dma(sbuf, 1000, 0x56);
    buf_verify(sbuf, 1000, 0x56);
    memset_dma(sbuf, 5000, 0x65);
    buf_verify(sbuf, 5000, 0x65);

    /* 2-byte set tests */
    dma_transfer_width = 2;
    memset_dma(dbuf, 10, 0xBE);
    buf_verify(dbuf, 10, 0xBE);
    memset_dma(dbuf, 100, 0xAC);
    buf_verify(dbuf, 100, 0xAC);
    memset_dma(dbuf, 1000, 0xD0);
    buf_verify(dbuf, 1000, 0xD0);
    memset_dma(dbuf, 5000, 0x12);
    buf_verify(dbuf, 5000, 0x12);

    /* 4-byte set tests */
    dma_transfer_width = 4;
    memset_dma(sbuf, 10, 0xA5);
    buf_verify(sbuf, 10, 0xA5);
    memset_dma(sbuf, 100, 0x5A);
    buf_verify(sbuf, 100, 0x5A);
    memset_dma(sbuf, 1000, 0x56);
    buf_verify(sbuf, 1000, 0x56);
    memset_dma(sbuf, 5000, 0x65);
    buf_verify(sbuf, 5000, 0x65);

    for(uint16_t i = 0; i < 5000; i++)
      sbuf[i] = i;

    /* MEMCOPY tests */
    /* No over lap */
    /* 1-byte transfers */
    dma_transfer_width = 1;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);

    /* 2-byte transfers */
    dma_transfer_width = 2;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);

    /* 4-byte transfers */
    dma_transfer_width = 4;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);

    /* With overlap tests (s > d) */
    /* 1-byte transfers */
    dma_transfer_width = 1;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);
    memmove_dma(dbuf+8, dbuf, 10);

    /* 2-byte transfers */
    dma_transfer_width = 2;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);
    memmove_dma(dbuf+8, dbuf, 10);

    /* 4-byte transfers */
    dma_transfer_width = 4;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);
    memmove_dma(dbuf+8, dbuf, 10);

    /* With overlap tests (s < d) */
    /* 1-byte transfers */
    dma_transfer_width = 1;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);
    memmove_dma(dbuf, dbuf+8, 10);

    /* 2-byte transfers */
    dma_transfer_width = 2;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);
    memmove_dma(dbuf, dbuf+8, 10);

    /* 4-byte transfers */
    dma_transfer_width = 4;
    memset_dma(dbuf, 5000, 0);
    memmove_dma(sbuf, dbuf, 5000);
    memmove_dma(dbuf, dbuf+8, 10);
    }
  free_words((uint32_t *)sbuf);
  free_words((uint32_t *)dbuf);
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief The function configures DMA as per arguments
 */
void dma_config(uint8_t ch, uint32_t src, uint32_t dest, uint8_t src_tf_wd,
                uint8_t dest_tf_wd, uint32_t sinc, uint8_t dinc,
                uint32_t length)
  {
  DMA_SAR(ch) = src;
  DMA_DAR(ch) = dest;
  DMA_DCR(ch) = DMA_DCR_AA(DMA_AUTO_ALIGN) +
    DMA_DCR_SSIZE(dma_width_calc(src_tf_wd)) +
    DMA_DCR_DSIZE(dma_width_calc(dest_tf_wd)) +
    DMA_DCR_SINC(sinc) + DMA_DCR_DINC(dinc) +
    DMA_DCR_EINT(ENABLE_DMA_INT);
  DMA_DSR_BCR(ch) = DMA_DSR_BCR_BCR(length);
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief DMA handler ISR
 */
void DMA0_IRQHandler()
  {
  DMA_DSR_BCR(0) |= DMA_DSR_BCR_DONE(1);
  }

/*---------------------------------------------------------------------------*/

void buf_verify(uint8_t *buf, uint32_t length, uint8_t val)
  {
  for(uint32_t i = 0; i != length; i++)
    {
    if(buf[i] != val)
      {
      while(1) {}
      }
    }
  }
