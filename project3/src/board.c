/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file board.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 23, 2017
 * @brief This file contains definition of board startup.
 */

#include "common_ccc.h"
#include "board.h"
//#include "led.h"
#include "uart.h"
//#include "spi.h"

/*---------------------------------------------------------------------------*/

void board_init(void)
  {
#if defined(PLATFORM_MTK)
  /* Enable ports */
  //led_board_init();
  uart_board_init();
  //spi_board_init();

  /* Configure device */
  //led_configure();
  uart_configure();
  //spi_configure();
#endif
  }
