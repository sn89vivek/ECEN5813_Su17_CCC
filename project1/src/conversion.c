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

#include "conversion.h"

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base)
{
	return 0;
}

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)
{
	return 0;
}

int8_t big_to_little32(uint32_t *data, uint32_t length)
{
	return 0;
}


/*---------------------------------------------------------------------------*/
/**
 * @brief The function little_to_big32 takes an array and size as
 *        inputs, and converts all words from little to big endian.
 *
 *        Little to big endian for a 32bit word conversion happens as follows:
 *        BYTE3 => BYTE0
 *        BYTE2 => BYTE1
 *        BYTE1 => BYTE2
 *        BYTE0 => BYTE3
 * 
 * @param data - array that needs to be converted
 * @param length - size of the array
 *
 * @return Returns SUCCESS if the array was successfully converted else returns
 *         FAILURE.
 */
int8_t little_to_big32(uint32_t *data, uint32_t length)
  {
    int8_t result;
    
    if(data == NULL || length <= 0)
      {
        result = FAILURE;
      }
    else
      {
        for (uint32_t *ptr1 = src, *end = src + length; ptr1 < end; ) 
          {
          *ptr1 = RSHIFT_3_BYTES(*ptr1) | BYTE1(RSHIFT_BYTE(*ptr1)) | 
                  BYTE2(LSHIFT_BYTE(*ptr1)) | BYTE3(LSHIFT_3_BYTES(*ptr1));
          }
        result = SUCCESS;
      }
    return result;  
  }