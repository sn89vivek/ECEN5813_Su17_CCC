/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file board_kl25z.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 23, 2017
 * @brief This file contains definition of board startup.
 */

#include "common_ccc.h"
#include "board.h"
#include "logger.h"
#include "led_kl25z.h"
#include "uart0_kl25z.h"
#include "timer_kl25z.h"
#include "memory_dma.h"
//#include "spi_kl25z.h"

/*---------------------------------------------------------------------------*/

void board_init(void)
  {
  log_init();
  log_item(LOGGER_INITIALIZED);

  /* Enable ports */
  led_board_init();
  timer_board_init();
  uart_board_init();
  dma_board_init();
  //spi_board_init();

  /* Configure device */
  led_configure();
  timer_configure();
  uart_configure();
  dma_configure();
  //spi_configure();

  log_item(GPIO_INITIALIZED);
  }
