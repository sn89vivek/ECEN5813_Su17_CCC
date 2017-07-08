/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file uart.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 5, 2017
 * @brief This file contains declaration of uart related drivers.
 */

#ifndef UART_H_
#define UART_H_

#include "common_ccc.h"

/*---------------------------------------------------------------------------*/

/* ---- UART config --- */
//#define UART_MODE_INTERRUPTS
#define ENABLE_CLK                (1)
#define DISABLE_CLK               (0)
#define PORTA_UART0_FUNC          (2)
#define TRANSMIT_ENABLE           (1)
#define RECEIVE_ENABLE            (1)

#define CLK_SRC_MCGPLLCLK_2       (1)
#define UART0_CLK_SRC             (CLK_SRC_MCGPLLCLK_2)
#define DISABLE_UART0()			  (UART0->C2 = 0)
#define ENABLE_UART0()            (UART0->C2 |= UART0_C2_RE(RECEIVE_ENABLE) + UART0_C2_TE(TRANSMIT_ENABLE))

#define UART_OSR_VAL			  (32)
#define UART_OSR_REG_VAL 		  (UART_OSR_VAL-1)

#define UART0_BAUD_RATE			  115200
#define BAUD_RATE_REG_VAL()       (SystemCoreClock/(UART_OSR_VAL + UART0_BAUD_RATE))
#define UART0_BAUD_REG_HIGH()     ((BAUD_RATE_REG_VAL() >> 8) & 0x0F)
#define UART0_BAUD_REG_LOW()      (BAUD_RATE_REG_VAL() & 0xFF)

/*---------------------------------------------------------------------------*/

/*
 * @brief This function configures UART peripheral
 *
 * @param None
 * @return None
 *
 */
void uart_configure();

#endif /* UART_H_ */
