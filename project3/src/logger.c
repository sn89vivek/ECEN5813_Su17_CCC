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

#include <stdio.h>
#include "common_ccc.h"
#include "logger.h"
#include "conversion.h"

/*---------------------------------------------------------------------------*/

#ifdef VERBOSE
void log_data(uint8_t *data, size_t length)
  {
  if (data != NULL)
    {
    for (uint8_t *ptr = data, *end = data + length; ptr < end; ptr++)
      {
      (void)fputc('.', stderr);
      }
    }
  }
#endif

/*---------------------------------------------------------------------------*/

#ifdef VERBOSE
void log_string(char8_t *str, size_t length)
  {
  if (str != NULL)
    {
    for (char8_t *ptr = str, *end = str + length; ptr < end; ptr++)
      {
      (void)fputc(*ptr, stderr);
      }
    }
  }
#endif

/*---------------------------------------------------------------------------*/

#ifdef VERBOSE
void log_zstring(char8_t *str)
  {
  if (str != NULL)
    {
    for (char8_t *ptr = str; *ptr != '\0'; ptr++)
      {
      (void)fputc(*ptr, stderr);
      }
    }
  }
#endif

/*---------------------------------------------------------------------------*/

#ifdef VERBOSE
void log_integer(int32_t value)
  {
  uint8_t buffer[1+10+1];
  if (my_itoa(value, buffer, 10) > 0)
    {
    (void)fprintf(stderr, "%s", buffer);
    }
  }
#endif

/*---------------------------------------------------------------------------*/

#ifdef VERBOSE
void log_flush()
  {
  (void)fflush(stderr);
  }
#endif
