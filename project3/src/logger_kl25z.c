/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file console_kl25z.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 4, 2017
 * @brief Definitions for console related functions.
 */

#ifdef VERBOSE

#include "common_ccc.h"
#include "logger.h"
#include "circbuf.h"
#include "conversion.h"
#include "uart0_kl25z.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */

/** Object: logger_tx: Logger Tx circular buffer */
CB_t *logger_tx;

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void UART0_IRQHandler();

/*---------------------------------------------------------------------------*/

void log_init(void)
  {
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

    if (queued > 0)
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

    if (queued > 0)
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
void UART0_IRQHandler()
  {
  uint8_t uart_char;
  CB_status status;

  /* Tx Queue */
  if ((UART0->S1 & UART0_S1_TDRE_MASK) && (UART0_TIE_ENABLED()))
    {
    /* Check if this is the last character */
    if (1 == CB_count(logger_tx))
      {
      UART0_DISABLE_TIE();
      }
    status = CB_buffer_remove_item(logger_tx, &uart_char);
    if (status != CB_SUCCESS)
      {
      while (1); /* Block on error */
      }
    uart_send((const uint8_t *)&uart_char);
    }
  }

/*---------------------------------------------------------------------------*/

#endif /* VERBOSE */
