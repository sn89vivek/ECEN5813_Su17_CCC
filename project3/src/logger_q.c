/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file logger.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 3, 2017
 * @brief Definitions for logger_q related functions.
 */

#ifdef VERBOSE

#include "common_ccc.h"
#include "logger.h"
#include "logger_q.h"
#include "memory.h"
#include "board.h"
#include "uart0_kl25z.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */

/** Object: logger_q_tx: Logger item-queue Tx circular buffer */
LOGQ_t *logger_q_tx;

/*---------------------------------------------------------------------------*/

LOGQ_status LOGQ_init(uint32_t length)
  {
  LOGQ_status status;

  if (length <= 1 || (length & (length - 1)) != 0)
    {
    status = LOGQ_LENGTH;
    }
  else
    {
    logger_q_tx = (LOGQ_t*)reserve_words(SIZEOF_IN_WORDS(LOGQ_t));
    if (NULL == logger_q_tx)
      {
      status = LOGQ_ENOMEM;
      }
    else
      {
      logger_q_tx->buf_start = (logger_item_t*)reserve_words(LENGTH_IN_WORDS(length));
      if (NULL == logger_q_tx->buf_start)
        {
        status = LOGQ_ENOMEM;
        }
      else
        {
        logger_q_tx->buf_end = logger_q_tx->buf_start + length - 1;
        logger_q_tx->head = logger_q_tx->buf_start;
        logger_q_tx->tail = logger_q_tx->buf_start;
        logger_q_tx->buf_size = length;
        logger_q_tx->count = 0;
        status = LOGQ_SUCCESS;
        }
      }
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

LOGQ_status LOGQ_destroy(void)
  {
  LOGQ_status status;

  if (NULL == logger_q_tx)
    {
    status = LOGQ_NULL;
    }
  else
    {
    free_words((uint32_t*)logger_q_tx->buf_start);
    free_words((uint32_t*)logger_q_tx);
    status = LOGQ_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

LOGQ_status LOGQ_add_item(logger_item_t *item)
  {
  LOGQ_status status;

  if (NULL == logger_q_tx)
    {
    status = LOGQ_NULL;
    }
  else if ((logger_q_tx->buf_size - logger_q_tx->count) < (5 + item->length))
    {
    status = LOGQ_BUFFER_FULL;
    }
  else
    {
    /* Add item to end of buffer with wrapping at bounds of memory */
    CRITICAL_SECTION_START();
    for (uint8_t *src = (uint8_t*)item,
         *end = (uint8_t*)item + sizeof(logger_item_t),
         *dst = (uint8_t*)logger_q_tx->tail; src < end; )
      {
      *dst++ = *src++;
      }
    logger_q_tx->tail = (logger_q_tx->tail < logger_q_tx->buf_end) ?
      logger_q_tx->tail + 1 : logger_q_tx->buf_start;
    logger_q_tx->count++;
    CRITICAL_SECTION_END();

    if (board_is_ready)
      {
      UART0_ENABLE_TIE();
      }

    status = LOGQ_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

logger_item_t *LOGQ_raw_remove_item(void)
  {
  logger_item_t *item;

  if (logger_q_tx->count > 0)
    {
	item = logger_q_tx->head;

    /* Remove item from front of buffer with wrapping at bounds of memory */
    logger_q_tx->head = (logger_q_tx->head < logger_q_tx->buf_end) ?
      logger_q_tx->head + 1 : logger_q_tx->buf_start;
    logger_q_tx->count--;
    }
  else
    {
    item = NULL;
    }

  return item;
  }

/*---------------------------------------------------------------------------*/

#endif /* VERBOSE */
