/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project2.c 
 * @brief This file defines the primary operation of project 2.
 *
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 15, 2017
 *
 */

#include "common_ccc.h"
#include "project2.h"

/*---------------------------------------------------------------------------*/

void project2(void) 
  {
#if defined(PLATFORM_MKL)
  uint8_t buffer[12];
  uart_configure();
  while (1)
    {
    uart_receive_n(buffer, 10);
    uart_send_n(buffer, 10);
    }
#endif
  }
