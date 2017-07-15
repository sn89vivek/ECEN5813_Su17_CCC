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
static void uart_port_init();

/*---------------------------------------------------------------------------*/

void uart_configure()
  {
  uart_port_init();

  /* **************************************************************************
   * # UART module configuration
   * **************************************************************************
   */

  /* Enable Clock to UART module */
  SIM->SCGC4 |= SIM_SCGC4_UART0(ENABLE_CLK);

  /* Select clock source */
  /* MCGPLLCLK_by_2 selected: 20971520Hz */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(UART0_CLK_SRC);

  /* Disable uart before any config settings */
  DISABLE_UART0();

  /* UART BAUD RATE */
  UART0->BDH |= UART0_BDH_SBR(UART0_BAUD_REG_HIGH());
  UART0->BDL |= UART0_BDL_SBR(UART0_BAUD_REG_LOW());

  /* UART_C1: Normal, Enabled_in_wait, 8-bit, parity disabled   */
  UART0->C1 = 0;

  /* UART_c4: Over Sampling Ratio setting */
  UART0->C4 = UART0_C4_OSR(UART_OSR_REG_VAL);

  UART0->C5 = UART0_C5_BOTHEDGE(1);

#if defined(UART_MODE_INTERRUPTS)
  /* Enable transmit and receive interrupts */
  UART0->C2 |= UART0_C2_TIE(TRANSMIT_INTERRUPT_ENABLE);
  UART0->C2 |= UART0_C2_TIE(RECEIVE_INTERRUPT_ENABLE);
#endif

  /* UART_Enable */
  ENABLE_UART0();

  uart_send_n((uint8_t *)"Hello World\n\r",13);
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_send_n(uint8_t *buf, uint32_t n)
  {
  if(buf == NULL)
  return FAILURE;
  while(n--)
    uart_send(buf++);
  return SUCCESS;
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_send(uint8_t *data)
  {
  if(data == NULL)
  return FAILURE;
  while(!(UART0->S1 & UART0_S1_TDRE_MASK)) {}
  UART0->D = *data;
  return SUCCESS;
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_receive_n(uint8_t *buf, uint32_t n)
  {
  if(buf == NULL)
  return FAILURE;
  while(n--)
    uart_receive(buf++);
  return SUCCESS;
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_receive(uint8_t *data)
  {
  if(data == NULL)
  return FAILURE;
  while(!(UART0->S1 & UART0_S1_RDRF_MASK)) {}
  *data = UART0->D;
  return SUCCESS;
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief This function initializes ports for UART
 *
 * @param None
 * @return None
 *
 * # Port Mapping table
 *
 * PTA1: UART0_RX (ALT2)
 * PTA2: UART0_TX (ALT2)
 */
void uart_port_init()
  {
  /* Enable clock to PORTA */
  SIM->SCGC5 |= SIM_SCGC5_PORTA(ENABLE_CLK);

  /* Configure Alternate functionality in appropriate Control register */
  PORTA_PCR1 |= PORT_PCR_MUX(PORTA_UART0_FUNC);
  PORTA_PCR2 |= PORT_PCR_MUX(PORTA_UART0_FUNC);
  }


