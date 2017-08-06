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
#include "logger_q.h"
#include "conversion.h"

/*---------------------------------------------------------------------------*/

void log_q_init(void)
  {
  }

/*---------------------------------------------------------------------------*/

void log_item(const logger_item_t * const item)
  {
  if (item != NULL)
    {
    (void)fputc(item->id <= 9 ? '0' + item->id : 'A' + (item->id-10), stderr);
    (void)fputc(SPACE, stderr);
    //TODO output item->timestamp
    (void)fputc(SPACE, stderr);
    if (item->data != NULL)
      {
      for (const uint8_t *ptr = item->data, *end = item->data + item->length;
           ptr < end; ptr++)
        {
        (void)fputc(*ptr, stderr);
        }
      }
    (void)fputc(CR, stderr);
    (void)fputc(LF, stderr);
    }
  }

/*---------------------------------------------------------------------------*/

#endif /* VERBOSE */
