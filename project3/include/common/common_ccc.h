/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file common_ccc.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 20, 2017
 * @brief Common definitions for use by the Crazy Crafty Coders.
 */

#ifndef __COMMON_CCC_H__
#define __COMMON_CCC_H__

/*---------------------------------------------------------------------------*/

#if defined(PLATFORM_HOST)

  #include <stdio.h>
  #include <stdbool.h>
  #include <stdint.h>
  #include <stdlib.h>
  #include <libio.h>
  #include <ctype.h>
  #include <time.h>

  #ifdef CMOCKA_UNIT_TESTS
    #include <stdarg.h>
    #include <setjmp.h>
    #include <cmocka.h>
  #endif

#elif defined(PLATFORM_BBB)

  #include <stdio.h>
  #include <stdbool.h>
  #include <stdint.h>
  #include <stdlib.h>
  #include <libio.h>
  #include <ctype.h>
  #include <time.h>

#elif defined(PLATFORM_MKL)

  #include <stdbool.h>
  #include <stdint.h>
  #include <ctype.h>
  #include <malloc.h>
  #include "MKL25Z4.h"
  #include "system_MKL25Z4.h"
  #include "nordic.h"

#else

  #error "Target platform is not supported: #include"

#endif

/*---------------------------------------------------------------------------*/

typedef uint8_t bool_t;

typedef char char8_t;

#if defined(PLATFORM_MKL)
typedef uint32_t time_t;
#endif

/*---------------------------------------------------------------------------*/

#if defined(PLATFORM_HOST)

  #define INLINE __attribute__( ( always_inline ) ) static inline

  #define CRITICAL_SECTION_START()
  #define CRITICAL_SECTION_END()

#elif defined(PLATFORM_BBB)

  #define INLINE __attribute__( ( always_inline ) ) static inline

  #define CRITICAL_SECTION_START()
  #define CRITICAL_SECTION_END()

#elif defined(PLATFORM_MKL)

  #define INLINE __attribute__( ( always_inline ) ) __STATIC_INLINE

  #define CRITICAL_SECTION_START()  __disable_irq()
  #define CRITICAL_SECTION_END()    __enable_irq()

#else

  #error "Target platform is not supported: #define"

#endif

/*---------------------------------------------------------------------------*/

#define HEX(i) ((i) <= 9 ? '0' + (i) : 'A' - 10 + (i))

/*---------------------------------------------------------------------------*/

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

/*---------------------------------------------------------------------------*/

#ifndef SUCCESS
#define SUCCESS (0)
#endif

#ifndef FAILURE
#define FAILURE (1)
#endif

/*---------------------------------------------------------------------------*/

#ifndef CR
#define CR (0x0D)
#endif

#ifndef LF
#define LF (0x0A)
#endif

#ifndef SPACE
#define SPACE (' ')
#endif

/*---------------------------------------------------------------------------*/

#endif /* __COMMON_CCC_H__ */
