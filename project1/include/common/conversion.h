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
 * @brief This file contains declaration of basic data manipulation functions.
 */

#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <stdint.h>

/*---------------------------------------------------------------------------*/

/* ---- Bitwise operations --- */
#define LSHIFT_BYTE(a)          ((a) << 8)
#define LSHIFT_2_BYTES(a)       ((a) << 16)
#define LSHIFT_3_BYTES(a)       ((a) << 24)

#define RSHIFT_BYTE(a)          ((a) >> 8)
#define RSHIFT_2_BYTES(a)       ((a) >> 16)
#define RSHIFT_3_BYTES(a)       ((a) >> 24)

#define BYTE0(a)                ((a) & 0xFF)
#define BYTE1(a)                ((a) & 0xFF00)
#define BYTE2(a)                ((a) & 0xFF0000)
#define BYTE3(a)                ((a) & 0xFF000000)

/* ---- Coversion operations --- */
#define MAX_CONVERSION_STRLEN (31)
#define ASCII_TO_INT(a)	      ((a) <= '9' ? (a) - '0' : ((a) - 'A') + 10)

/*---------------------------------------------------------------------------*/

/**
 * @brief The function my_itoa() converts data from a standard integer type
 *        into an ASCII string.
 *
 * @param data - Integer to convert
 * @param ptr - Pointer to output character set
 * @param base - Target base from 2 and 16
 *
 * @return Returns FAILURE if the conversion failed
 * @return Returns SUCCESS if the data was successfully converted
 */
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);

/**
 * @brief The function my_atoi() converts data from an ASCII string into a
 *        standard integer type.
 *
 * Notes on implementation:
 * 	- The input string must be a representaion of a positive number in a base
 *	  between 2-16. This function does not support radix-complement 
 *    representation in any base
 *	- Negative number representation must have first character as '-' 
 *  - A preceding '+' sign is not supported
 *  - @p digits must include '-' sign and not include null character.
 *  - A-H for base 16 must be in uppercase only
 *  - Any characters after MAX_CONVERSION_STRLEN will not be parsed
 * 
 * @param ptr - Pointer to input character set
 * @param digits - Number of digits in character set including '-' sign and
 *				   excluding null terminator
 * @param base - Source base from 2 and 16
 * @param data - If conversion suceeds, the number is written to this variable.
 *
 * @return Returns FAILURE if the conversion failed
 * @return Returns SUCCESS if the data was successfully converted
 */
uint8_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base, int32_t *data);

/**
 * @brief The function big_to_little() takes an array of data in memory from a
 *        big endian representation to little endian.
 *
 * @param data - Pointer to data array
 * @param length - Number of 32bit values to convert
 *
 * @return Returns FAILURE if the conversion failed
 * @return Returns SUCCESS if the array was successfully converted
 */
int8_t big_to_little32(uint32_t * data, uint32_t length);

/**
 * @brief The function little_to_big32() takes an array and size as inputs,
 *        and converts all words from little to big endian.
 *
 *        Little to big endian for a 32bit word conversion happens as follows:
 *          BYTE3 => BYTE0
 *          BYTE2 => BYTE1
 *          BYTE1 => BYTE2
 *          BYTE0 => BYTE3
 *
 * @param data - array that needs to be converted
 * @param length - size of the array
 *
 * @return Returns SUCCESS if the array was successfully converted else returns
 *         FAILURE.
 */
int8_t little_to_big32(uint32_t * data, uint32_t length);

/*---------------------------------------------------------------------------*/

#endif /* __CONVERSION_H__ */
