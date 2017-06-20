/**
 * @file conversion.h
 * @brief Macros and prototypes for basic data manipulation
 *
 * TODO
 *
 * @author Robert Blazewicz/Vivek Sankaranarayanan
 * @date June 19, 2017
 */

#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <stdint.h>

/*---------------------------------------------------------------------------*/
/* ---- Bitwise operations --------- */
#define LSHIFT_BYTE(a)		(a) << 8
#define LSHIFT_2_BYTES(a)	(a) << 16
#define LSHIFT_3_BYTES(a)	(a) << 24

#define RSHIFT_BYTE(a)		(a) >> 8
#define RSHIFT_2_BYTES(a)	(a) >> 16
#define RSHIFT_3_BYTES(a)	(a) >> 24

#define	BYTE0(a)			(a) & 0xFF
#define	BYTE1(a)			(a) & 0xFF00
#define	BYTE2(a)			(a) & 0xFF0000
#define	BYTE3(a)			(a) & 0xFF000000

/*---------------------------------------------------------------------------*/
/* ---- Function Prototypes --------- */
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);
int8_t big_to_little32(uint32_t * data, uint32_t length);
int8_t little_to_big32(uint32_t * data, uint32_t length);

#endif