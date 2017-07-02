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
 * @brief Common defintions for use by the Crazy Crafty Coders.
 */

#ifndef __COMMON_CCC_H__
#define __COMMON_CCC_H__

/*---------------------------------------------------------------------------*/

#if defined(PLATFORM_HOST) || defined(PLATFORM_BBB) 

  #include <stdbool.h>
  #include <stdint.h>
  #include <stdlib.h>
  #include <libio.h>

  #ifdef CMOCKA_UNIT_TESTS
    #include <stdarg.h>
    #include <setjmp.h>
    #include <cmocka.h>
  #endif

#elif defined(PLATFORM_MKL)

  #include <stdbool.h>
  #include <stdint.h>
  #include <malloc.h>
  #include "MKL25Z4.h"
  #include "system_MKL25Z4.h"

#else

  #error "Target platform is not supported"

#endif

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

/*---------------------------------------------------------------------------*/

typedef char char8_t;

/*---------------------------------------------------------------------------*/

#endif /* __COMMON_CCC_H__ */
