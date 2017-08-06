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
 * @date August 5, 2017
 * @brief This file contains definition of board startup.
 */

#include "common_ccc.h"
#include "board.h"
#include "logger.h"

/*---------------------------------------------------------------------------*/

void board_init(void)
  {
  log_init();
  log_item(LOGGER_INITIALIZED);

  /* Enable ports */

  /* Configure device */

  //log_id1(GPIO_INITIALIZED);
  }