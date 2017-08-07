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
#include "rtc_kl25z.h"
#include "led_kl25z.h"
#include "uart0_kl25z.h"
#include "timer_kl25z.h"
#include "memory_dma.h"
#include "spi_kl25z.h"

/*---------------------------------------------------------------------------*/

/** Object: board_is_ready: Indicates that the board is ready to be used. */
bool_t board_is_ready;

/*---------------------------------------------------------------------------*/

void board_init(void)
  {
  log_init();
  log_item(LOGGER_INITIALIZED);

  /* Enable ports */
  rtc_board_init();
  led_board_init();
  timer_board_init();
  uart_board_init();
  dma_board_init();
  GPIO_nrf_init();

  /* Configure device */
  rtc_configure();
  led_configure();
  timer_configure();
  uart_configure();
  dma_configure();
  spi_configure();

  log_item(GPIO_INITIALIZED);

  /* Enable interrupts at CPU level */
  __enable_irq();

  board_is_ready = TRUE;
  }
