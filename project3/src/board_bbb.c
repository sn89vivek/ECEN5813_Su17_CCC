/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file board_bbb.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 3, 2017
 * @brief This file contains definition of board startup.
 */

#include "common_ccc.h"
#include "board.h"
#include "logger.h"
#include "logger_q.h"
//#include "led.h"
//#include "uart.h"
//#include "timer.h"
//#include "spi.h"

/*---------------------------------------------------------------------------*/

void board_init(void)
  {
  log_init();
  log_q_init();
  log_id1(LOGGER_INITIALIZED);

  /* Enable ports */
  //led_board_init();
  //timer_board_init();
  //uart_board_init();
  //spi_board_init();

  /* Configure device */
  //led_configure();
  //timer_configure();
  //uart_configure();
  //spi_configure();

  log_id1(GPIO_INITIALIZED);
  }
