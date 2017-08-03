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
#include "board.h"
#include "led.h"

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

  /* Modulate the Red LED at 50% duty cycle */
  led_modulate();

  /* Enable interrupts at CPU level */
  __enable_irq();

  while (1)
    {
    }
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */

#endif /* PROJECT3 */
