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

#include <string.h>
#include "common_ccc.h"
#include "project3.h"
#include "logger.h"

#if defined(PLATFORM_HOST)

void project3()
  {
  log_item(SYSTEM_INITIALIZED);
  log_item(SYSTEM_HALTED);
  }

#elif defined(PLATFORM_BBB)

#include "board.h"

void project3()
  {
  log_item(SYSTEM_INITIALIZED);
  log_item(SYSTEM_HALTED);
  }

#elif defined(PLATFORM_MKL)

#include "board.h"
#include "led_kl25z.h"
#include "memory_dma.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */


/*---------------------------------------------------------------------------*/
/* Declarations                                                              */


/*---------------------------------------------------------------------------*/

void project3()
  {
  board_init();

  log_string("Hello World\n");

  /* Modulate the Red LED at 50% duty cycle */
  led_modulate();

  log_item(SYSTEM_INITIALIZED);

  dma_memory_tests();

  while (1)
    {
    }

  log_item(SYSTEM_HALTED);
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */

#endif /* PROJECT3 */
