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

#include <stdio.h>
#include "common_ccc.h"
#include "logger.h"
#include "conversion.h"

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

#endif /* VERBOSE */
