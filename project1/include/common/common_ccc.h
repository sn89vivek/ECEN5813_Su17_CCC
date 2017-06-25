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

#ifdef PLATFORM_HOST

  #include <libio.h>
  #include <stdlib.h>

#else

  #define NULL ((void*)0)

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

#ifndef LF
#define LF (0x0A)
#endif

#ifndef CR
#define CR (0x0D)
#endif

/*---------------------------------------------------------------------------*/

typedef char char8_t;

/*---------------------------------------------------------------------------*/

#endif /* __COMMON_CCC_H__ */
