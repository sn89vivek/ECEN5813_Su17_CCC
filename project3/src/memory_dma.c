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
#include "logger.h"
#include "timer_kl25z.h"
#include "string.h"

/*---------------------------------------------------------------------------*/

#define ENABLE_CLK                  (1)
#define ENABLE_DMA_INT              (1)
#define DMA_AUTO_ALIGN              (1)
#define DMA_DEST_INC                (1)

#define TF_SIZE1                    (10)
#define TF_SIZE2                    (100)
#define TF_SIZE3                    (1000)
#define TF_SIZE4                    (5000)
/*---------------------------------------------------------------------------*/

typedef enum
  {
  TEST_MEMSET,
  TEST_MEMCOPY_NOOVERLAP,
  TEST_MEMCOPY_OVERLAP1,
  TEST_MEMCOPY_OVERLAP2
  } mem_test_t;

/*---------------------------------------------------------------------------*/

/** Object: dma_transfer_width: TBD */
static uint8_t dma_transfer_width;

/*---------------------------------------------------------------------------*/

void DMA0_IRQHandler();
void dma_config(uint8_t ch, uint32_t src, uint32_t dest, uint8_t src_tf_wd,
                uint8_t dest_tf_wd, uint32_t sinc, uint8_t dinc,
                uint32_t length);
void buf_verify(uint8_t *buf, uint32_t length, uint8_t val);
void log_profiling_result(const uint32_t ticks, const uint8_t transfer_width,
                          const mem_test_t mem_test);

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
  sbuf = (uint8_t *)reserve_words(LENGTH_IN_WORDS(TF_SIZE4));
  dbuf = (uint8_t *)reserve_words(LENGTH_IN_WORDS(TF_SIZE4));
  if((dbuf != NULL) && (sbuf != NULL))
    {
    log_item(PROFILING_STARTED);

    /* SET TESTS */

    /* TF_SIZE1 set tests */

    /* library */
    timer_reset();
    memset(dbuf, 0xAA, TF_SIZE1);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* manual */
    timer_reset();
    my_memset(dbuf, TF_SIZE1, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 1byte */
    dma_transfer_width = 1;
    timer_reset();
    my_memset(dbuf, TF_SIZE1, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 2byte */
    dma_transfer_width = 2;
    timer_reset();
    my_memset(dbuf, TF_SIZE1, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 4byte */
    dma_transfer_width = 4;
    timer_reset();
    my_memset(dbuf, TF_SIZE1, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* TF_SIZE2 set tests */

    /* library */
    timer_reset();
    memset(dbuf, 0xAA, TF_SIZE2);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* manual */
    timer_reset();
    my_memset(dbuf, TF_SIZE2, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 1byte */
    dma_transfer_width = 1;
    timer_reset();
    my_memset(dbuf, TF_SIZE2, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 2byte */
    dma_transfer_width = 2;
  timer_reset();
  my_memset(dbuf, TF_SIZE2, 0xAA);
  log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
  log_flush();

  /* dma - 4byte */
  dma_transfer_width = 4;
  timer_reset();
  my_memset(dbuf, TF_SIZE2, 0xAA);
  log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
  log_flush();


    /* TF_SIZE3 set tests */

    /* library */
    timer_reset();
    memset(dbuf, 0xAA, TF_SIZE3);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* manual */
    timer_reset();
    my_memset(dbuf, TF_SIZE3, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 1byte */
    dma_transfer_width = 1;
    timer_reset();
    my_memset(dbuf, TF_SIZE3, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 2byte */
    dma_transfer_width = 2;
  timer_reset();
  my_memset(dbuf, TF_SIZE3, 0xAA);
  log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
  log_flush();

  /* dma - 4byte */
  dma_transfer_width = 4;
  timer_reset();
  my_memset(dbuf, TF_SIZE3, 0xAA);
  log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
  log_flush();

    /* TF_SIZE4 set tests */

    /* library */
    timer_reset();
    memset(dbuf, 0xAA, TF_SIZE4);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* manual */
    timer_reset();
    my_memset(dbuf, TF_SIZE4, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 1byte */
    dma_transfer_width = 1;
    timer_reset();
    my_memset(dbuf, TF_SIZE4, 0xAA);
    log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
    log_flush();

    /* dma - 2byte */
    dma_transfer_width = 2;
  timer_reset();
  my_memset(dbuf, TF_SIZE4, 0xAA);
  log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
  log_flush();

  /* dma - 4byte */
  dma_transfer_width = 4;
  timer_reset();
  my_memset(dbuf, TF_SIZE4, 0xAA);
  log_profiling_result(timer_ticks(), dma_transfer_width, TEST_MEMSET);
  log_flush();

    }

  log_item(PROFILING_COMPLETED);
  log_flush();
  free_words((uint32_t *)sbuf);
  free_words((uint32_t *)dbuf);
  }

/*---------------------------------------------------------------------------*/

/**
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

/**
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

/*---------------------------------------------------------------------------*/

/**
 * @brief Function log_item2(PROFILING_RESULT, () logs
 *
 * @param ticks - Elapsed ticks
 * @param transfer_width - DMA transfer width
 * @param mem_test - Memory test type
 *
 * @return None
 */
void log_profiling_result(const uint32_t ticks, const uint8_t transfer_width, const mem_test_t mem_test)
  {
  uint8_t data[6];
  data[0] = (ticks & 0xFF000000) >> 24;
  data[1] = (ticks & 0x00FF0000) >> 16;
  data[2] = (ticks & 0x0000FF00) >> 8;
  data[3] =  ticks & 0x000000FF;
  data[4] = transfer_width;
  data[5] = mem_test;
  log_item3(PROFILING_RESULT, (const uint8_t * const)&data, sizeof(data));
//  log_item2(PROFILING_RESULT, ticks);
  }
