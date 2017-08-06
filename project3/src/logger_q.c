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

    status = LOGQ_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

LOGQ_status LOGQ_remove_item(logger_item_t *item)
  {
  LOGQ_status status;

  if (NULL == logger_q_tx || NULL == item)
    {
    status = LOGQ_NULL;
    }
  else if (0 == logger_q_tx->count)
    {
    status = LOGQ_BUFFER_EMPTY;
    }
  else
    {
    /* Remove item from front of buffer with wrapping at bounds of memory */
    CRITICAL_SECTION_START();
    for (uint8_t *src = (uint8_t*)logger_q_tx->head,
         *end = (uint8_t*)logger_q_tx->head + sizeof(logger_item_t),
         *dst = (uint8_t*)item; src < end; )
      {
      *dst++ = *src++;
      }
    logger_q_tx->head = (logger_q_tx->head < logger_q_tx->buf_end) ?
      logger_q_tx->head + 1 : logger_q_tx->buf_start;
    logger_q_tx->count--;
    CRITICAL_SECTION_END();
    status = LOGQ_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

LOGQ_status LOGQ_is_full(void)
  {
  LOGQ_status status;

  if (NULL == logger_q_tx)
    {
    status = LOGQ_NULL;
    }
  else
    {
    status = (logger_q_tx->buf_size == logger_q_tx->count) ? LOGQ_SUCCESS : LOGQ_LENGTH;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

LOGQ_status LOGQ_is_empty(void)
  {
  LOGQ_status status;

  if (NULL == logger_q_tx)
    {
    status = LOGQ_NULL;
    }
  else
    {
    status = (0 == logger_q_tx->count) ? LOGQ_SUCCESS : LOGQ_LENGTH;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

#endif /* VERBOSE */
