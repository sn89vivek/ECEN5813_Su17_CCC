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
 * @brief Definitions for logger related functions.
 */

#ifdef VERBOSE

#include "common_ccc.h"
#include "logger.h"
#include "conversion.h"
#include "rtc.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */

/** Object: logger_rx: Logger Rx circular buffer */
CB_t *logger_rx;

/** Object: logger_tx: Logger Tx circular buffer */
CB_t *logger_tx;

/*---------------------------------------------------------------------------*/

void log_init(void)
  {
  }

/*---------------------------------------------------------------------------*/

void log_data(const uint8_t * const data,
              const size_t length)
  {
  if (data != NULL)
    {
    for (const uint8_t *ptr = data, *end = data + length; ptr < end; ptr++)
      {
      (void)fputc(*ptr, stderr);
      }
    }
  }

/*---------------------------------------------------------------------------*/

void log_string(const char8_t * const str)
  {
  if (str != NULL)
    {
    for (const char8_t *ptr = str; *ptr != '\0'; ptr++)
      {
      (void)fputc(*ptr, stderr);
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

void log_flush()
  {
  (void)fflush(stderr);
  }

/*---------------------------------------------------------------------------*/

void log_item(const logger_id_t id)
  {
  (void)fprintf(stderr, "^%02X %08lX 0 \n", id, rtc_now());
  }

/*---------------------------------------------------------------------------*/

void log_item2(const logger_id_t id,
               const uint8_t * const data,
               const uint8_t length)
  {
  char8_t buffer[16];

  buffer[0] = '\0';
  (void)my_itoa(length, (uint8_t*)buffer, 10);

  (void)fprintf(stderr, "^%02X %08lX %s ", id, rtc_now(), buffer);
  if (data != NULL)
    {
    for (const uint8_t *ptr = data, *end = data + length; ptr < end; ptr++)
      {
      (void)fputc(*ptr, stderr);
      }
    }
  (void)fputc(CR, stderr);
  (void)fputc(LF, stderr);
  }

/*---------------------------------------------------------------------------*/

#endif /* VERBOSE */
