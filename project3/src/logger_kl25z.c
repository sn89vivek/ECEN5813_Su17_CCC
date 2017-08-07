/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file logger_kl25z.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 4, 2017
 * @brief Definitions for console related functions.
 */

#ifdef VERBOSE

#include "common_ccc.h"
#include "logger.h"
#include "logger_q.h"
#include "circbuf.h"
#include "conversion.h"
#include "board.h"
#include "uart0_kl25z.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */

/** Object: logger_rx: Logger Rx circular buffer */
CB_t *logger_rx;

/** Object: logger_tx: Logger Tx circular buffer */
CB_t *logger_tx;

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void UART0_IRQHandler(void);

/*---------------------------------------------------------------------------*/

void log_init(void)
  {
  CB_status status;

  /* Create Rx buffer */
  status = CB_init(&logger_rx, MAX_LOGGER_LEN);
  if (status != CB_SUCCESS)
    while (1);

  /* Create Tx buffer */
  status = CB_init(&logger_tx, MAX_LOGGER_LEN);
  if (status != CB_SUCCESS)
    while (1);

  /* Create logger_q Tx buffer */
  status = LOGQ_init(MAX_LOGGER_LEN);
  if (status != CB_SUCCESS)
    while (1);
  }

/*---------------------------------------------------------------------------*/

void log_data(const uint8_t * const data,
              const size_t length)
  {
  size_t queued;
  const uint8_t * ptr;

  if (data != NULL)
    {
    queued = 0;
    ptr = data;

    while (queued < length)
      {
      const CB_status status = CB_buffer_add_item(logger_tx, *ptr);
      switch (status)
        {
        case CB_BUFFER_FULL:
          continue;
        case CB_SUCCESS:
          queued++;
          ptr++;
          break;
        default:
          break;
        }
      }

    if (board_is_ready && queued > 0)
      {
      UART0_ENABLE_TIE();
      }
    }
  }

/*---------------------------------------------------------------------------*/

void log_string(const char8_t * const str)
  {
  size_t queued;
  const char8_t * ptr;

  if (str != NULL)
    {
    queued = 0;
    ptr = str;

    while (*ptr != '\0')
      {
      const CB_status status = CB_buffer_add_item(logger_tx, *ptr);
      switch (status)
        {
        case CB_BUFFER_FULL:
          continue;
        case CB_SUCCESS:
          queued++;
          ptr++;
          break;
        default:
          break;
        }
      }

    if (board_is_ready && queued > 0)
      {
      UART0_ENABLE_TIE();
      }
    }
  }

/*---------------------------------------------------------------------------*/

void log_integer(const int32_t value)
  {
  char8_t buffer[16];
  uint8_t digits;

  /* Convert value to base-10 ASCII */
  digits = my_itoa(value, (uint8_t*)buffer, 10);
  if (digits > 0)
    {
    log_string(buffer);
    }
  }

/*---------------------------------------------------------------------------*/

void logger_flush()
  {
  while (CB_is_empty(logger_tx) != CB_SUCCESS);
  }

/*---------------------------------------------------------------------------*/

void log_item(const logger_id_t id)
  {
  logger_item_t item;

  item.id = id;
  item.timestamp = 0xDEADBEEF;
  item.length = 0;

  (void)LOGQ_add_item(&item);
  }

/*---------------------------------------------------------------------------*/

void log_item2(const logger_id_t id,
               const uint32_t value)
  {
  logger_item_t item;

  item.id = id;
  item.timestamp = 0xDEADBEEF;
  item.length = 4;
  item.data[0] = (value & 0xFF000000) >> 24;
  item.data[1] = (value & 0x00FF0000) >> 16;
  item.data[2] = (value & 0x0000FF00) >> 8;
  item.data[3] =  value & 0x000000FF;

  (void)LOGQ_add_item(&item);
  }

/*---------------------------------------------------------------------------*/

void log_item3(const logger_id_t id,
               const uint8_t * const data,
               const uint8_t length)
  {
  logger_item_t item;

  item.id = id;
  item.timestamp = 0xDEADBEEF;
  if (NULL == data)
    {
    item.length = 0;
    }
  else
    {
    item.length = (length < 8) ? length : 8;
    for (uint8_t *src = (uint8_t*)data, *end = (uint8_t*)data + item.length,
         *dst = item.data; src < end; )
      {
      *dst++ = *src++;
      }
    }

  (void)LOGQ_add_item(&item);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief UART0 Interrupt handler
 *
 * This ISR handles transmission via UART8 from Tx circular buffer.
 *
 * @note Unsuccessful CB operations result in a blocking fault.
 *
 * @param none
 *
 * @return none
 */
void UART0_IRQHandler(void)
  {
  /* Log item Tx Queue */
  if (CB_SUCCESS != CB_is_empty(logger_tx) &&
      LOGQ_SUCCESS != LOGQ_is_empty())
    {
    logger_item_t *item;
    CRITICAL_SECTION_START();
    item = LOGQ_raw_remove_item();
    if (item != NULL)
      {
      CB_raw_add_item(logger_tx, '^');
      CB_raw_add_item(logger_tx, HEX((item->id & 0xF0) >> 4));
      CB_raw_add_item(logger_tx,  HEX(item->id & 0x0F));
      CB_raw_add_item(logger_tx, ' ');
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0xF0000000) >> 28));
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0x0F000000) >> 24));
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0x00F00000) >> 20));
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0x000F0000) >> 16));
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0x0000F000) >> 12));
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0x00000F00) >> 8));
      CB_raw_add_item(logger_tx, HEX((item->timestamp & 0x000000F0) >> 4));
      CB_raw_add_item(logger_tx,  HEX(item->timestamp & 0x0000000F));
      CB_raw_add_item(logger_tx, ' ');
      CB_raw_add_item(logger_tx, HEX((item->length & 0xF0) >> 4));
      CB_raw_add_item(logger_tx,  HEX(item->length & 0x0F));
      for (uint8_t *ptr = item->data, *end = item->data + item->length; ptr < end; ptr++)
        {
        CB_raw_add_item(logger_tx, HEX((*ptr & 0xF0) >> 4));
        CB_raw_add_item(logger_tx,  HEX(*ptr & 0x0F));
        }
      CB_raw_add_item(logger_tx, CR);
      CB_raw_add_item(logger_tx, LF);
      }
    CRITICAL_SECTION_END();
    }

  /* Log Tx Queue */
  if (CB_SUCCESS != CB_is_empty(logger_tx) &&
      (UART0->S1 & UART0_S1_TDRE_MASK) && UART0_TIE_ENABLED())
    {
    /* Check if this is the last character */
    if (1 == CB_count(logger_tx) && LOGQ_SUCCESS == LOGQ_is_empty())
      {
      UART0_DISABLE_TIE();
      }
    uint8_t uart_char;
    if (CB_SUCCESS == CB_buffer_remove_item(logger_tx, &uart_char))
      {
      uart_send((const uint8_t *)&uart_char);
      }
    }

  /* Log Rx Queue */
  if (CB_SUCCESS != CB_is_full(logger_rx) &&
      (UART0->S1 & UART0_S1_RDRF_MASK))
    {
    uint8_t uart_char;
    uart_receive(&uart_char);
    (void)CB_buffer_add_item(logger_rx, uart_char);
    }
  }

/*---------------------------------------------------------------------------*/

#endif /* VERBOSE */
