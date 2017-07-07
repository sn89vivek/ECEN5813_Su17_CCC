/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file uart.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 5, 2017
 * @brief This file contains definition of uart drivers
 */

#include "uart.h"

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

static void port_init();

/*
 * # Port Mapping table
 *
 * PTA1: UART0_RX (ALT2)
 * PTA2: UART0_TX (ALT2)
 */
void port_init()
  {
  /* Enable clock to PORTA */
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

  /* Configure Alternate functionality in appropriate Control register */
  PORTA_PCR1 |= (PORTA_UART0_FUNC << PORT_PCR_MUX_SHIFT);
  PORTA_PCR2 |= (PORTA_UART0_FUNC << PORT_PCR_MUX_SHIFT);
  }

void uart_configure()
  {
  port_init();
  }
