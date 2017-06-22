/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file conversion.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 19, 2017
 * @brief This file contains definition of basic data manipulation functions.
 */

#include <libio.h>
#include "conversion.h"
#include "common_ccc.h"

/*---------------------------------------------------------------------------*/

/* ---- Local function declarations --- */
uint32_t place_value_get(uint32_t num, uint8_t pow);

/*---------------------------------------------------------------------------*/

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base)
  {
  return 0;
  }

/*---------------------------------------------------------------------------*/

uint8_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base, int32_t *data)
  {
  int8_t sign = 1;
  uint8_t result = SUCCESS;
  uint8_t num;
  uint32_t value = 0;

  if(ptr == NULL)
    result = FAILURE;
  else
    {
    if(*ptr == '-')
      {
      sign = -1;
      digits -=1;
      ptr++;
      }

    if(digits > MAX_CONVERSION_STRLEN)
      digits = MAX_CONVERSION_STRLEN;

    for(;digits != 0; digits--, ptr++)
      {
      if(ptr == '\0')
        {
        /* digits parameter cannot be trusted */
        result = FAILURE;
        break;
        }
      num = ASCII_TO_INT(*ptr);
      if(num >= base)
        {
        /* Illegal character for the given base */  
        result = FAILURE;
        break;
        }
      value += (value*place_value_get(base, digits));
      }
    }
  *data = value*sign; 
  return result;
  }

/*---------------------------------------------------------------------------*/

int8_t big_to_little32(uint32_t *data, uint32_t length)
  {
  int8_t result;

  if (NULL == data || length <= 0)
    {
    result = FAILURE;
    }
  else
    {
    for (uint32_t *ptr = data, *end = data + length; ptr < end; ptr++)
      {
      *ptr = ((*ptr & 0x000000FF) << 24) |
             ((*ptr & 0x0000FF00) <<  8) |
             ((*ptr & 0x00FF0000) >>  8) |
             ((*ptr & 0xFF000000) >> 24);
      }
    result = SUCCESS;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

int8_t little_to_big32(uint32_t *data, uint32_t length)
  {
  int8_t result;

  if (data == NULL || length <= 0)
    {
    result = FAILURE;
    }
  else
    {
    for (uint32_t *ptr = data, *end = data + length; ptr < end; )
      {
      *ptr = (RSHIFT_3_BYTES(*ptr)) | 
             (BYTE1(RSHIFT_BYTE(*ptr))) |
             (BYTE2(LSHIFT_BYTE(*ptr))) | 
             (BYTE3(LSHIFT_3_BYTES(*ptr)));
      }
    result = SUCCESS;
    }

  return result;
  }

/*---------------------------------------------------------------------------*/

uint32_t place_value_get(uint32_t num, uint8_t pow)
  {
  uint32_t result = 1;  
  while(pow--)
    result *= num;
  return result;  
  }
