/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project3.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 22, 2017
 * @brief This file contains definition of project3 related tasks
 */

#if defined(PROJECT3)

#include "common_ccc.h"
#include "project3.h"

#if defined(PLATFORM_HOST)

void project3()
  {
  }

#elif defined(PLATFORM_BBB)

void project3()
  {
  }

#elif defined(PLATFORM_MKL)

#include "board.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */


/*---------------------------------------------------------------------------*/
/* Declarations                                                              */


/*---------------------------------------------------------------------------*/

void project3()
  {
  board_init();
  uart_interrupts_enable();
  dma_memory_tests();
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */

#endif /* PROJECT3 */
