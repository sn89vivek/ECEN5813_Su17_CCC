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

#include "common_ccc.h"
#include "uart.h"

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void uart_port_init();

/*---------------------------------------------------------------------------*/

void uart_configure()
  {
  /* Initialize port for operation of UART0 */
  uart_port_init();

  /* Enable Clock to UART0 module
   *  - System Clock Gating Control Register 4 (SIM_SCGC4)
   *    Set bit 10 to enable clock gate to the UART0 module.
   */
  SIM->SCGC4 |= SIM_SCGC4_UART0(ENABLE_CLK);

  /* Select UART0 clock source
   *  - System Options Register 2 (SIM_SOPT2)
   *    Set bits 27-26 to set the UART0 clock source.
   *      MCGPLLCLK_by_2 selected: 20971520Hz
   */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(CLK_SRC_MCGPLLCLK_2);

  /** Disable UART0 before setting configuration */
  DISABLE_UART0();

  /* Set the prescale divisor for UART0 baud rate
   *  - UART Baud Rate Register High (UARTx_BDH)
   *  - UART Baud Rate Register Low  (UARTx_BDL)
   *    Set the stop bit number
   *    Set the baud rate
   */
  UART0->BDH |= UART0_BDH_SBR(UART0_BAUD_REG_HIGH) | UART0_BDH_SBNS(ONE_STOP_BIT);
  UART0->BDL |= UART0_BDL_SBR(UART0_BAUD_REG_LOW);

  /* Set UART0 features
   *  - UART CONTROL Register 1 (UARTx_C1)
   *    Normal
   *    Enabled_in_wait
   *    8-bit
   *    Parity disabled
   */
  UART0->C1 = 0;

  /* Over Sampling Ratio setting
   *  - UART Control Register 4 (UARTx_C4)
   *    Set the over sampling ratio for the receiver.
   */
  UART0->C4 = UART0_C4_OSR(UART_OSR_VAL - 1);

  /* Both Edge Sampling
   *  - UART Control Register 5 (UARTx_C5)
   *    Enable both-edge-sampling
   */
  UART0->C5 = UART0_C5_BOTHEDGE(1);

  /* Enable UART0 */
  ENABLE_UART0();
  }

/*---------------------------------------------------------------------------*/

void uart_interrupts_enable()
  {
  /* Enable UART0 receiver interrupt for RDRF */
  UART0->C2 |= UART0_C2_RIE(RECEIVE_INTERRUPT_ENABLE);

  /* Enable UART0 interrupts and set priority at NVIC level */
  NVIC_EnableIRQ(UART0_IRQn);
  NVIC_SetPriority(UART0_IRQn, 0);

  /* Enable interrupts at CPU level */
  __enable_irq();
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_send_n(const uint8_t *buf, uint32_t n)
  {
  uint8_t status;
  if (buf == NULL)
    {
    status = FAILURE;
    }
  else
    {
    while (n--)
      {
      uart_send(buf++);
      }
    status = SUCCESS;
    }
  return status;
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_send(const uint8_t *data)
  {
  uint8_t status;
  if (data == NULL)
    {
    status = FAILURE;
    }
  else
    {
    /* Spin waiting for room to write data to the transmit data buffer */
    while (!(UART0->S1 & UART0_S1_TDRE_MASK))
      {
      }
    /* Write to the UART data register (UART_D) */
    UART0->D = *data;
    status = SUCCESS;
    }
  return status;
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_receive_n(uint8_t *buf, uint32_t n)
  {
  uint8_t status;
  if (buf == NULL)
    {
    status = FAILURE;
    }
  else
    {
    while (n--)
      {
      uart_receive(buf++);
      }
      status = SUCCESS;
    }
  return status;
  }

/*---------------------------------------------------------------------------*/

uint8_t uart_receive(uint8_t *data)
  {
  uint8_t status;
  if (data == NULL)
    {
    status = FAILURE;
    }
  else
    {
    /* Spin waiting for receive data */
    while (!(UART0->S1 & UART0_S1_RDRF_MASK))
      {
      }
    /* Read the UART data register (UART_D) */
    *data = UART0->D;
    status = SUCCESS;
    }
  return status;
  }

/*---------------------------------------------------------------------------*/

void uart_print_string(const uint8_t *str)
  {
  uint32_t len;
  if (str != NULL)
    {
    for (const uint8_t * ptr = str; *ptr != '\0'; ptr++, len++)
      {
      }
    if (len > 0)
      {
      uart_send_n(str, len);
      }
    }
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief This function initializes the port of UART0
 *
 * @param None
 * @return None
 */
void uart_port_init()
  {
  /** Enable clock to PORTA
   *  - System Clock Gating Control Register 5 (SIM_SCGC5)
   *    Enable Port A Clock Gate Control
   */
  SIM->SCGC5 |= SIM_SCGC5_PORTA(ENABLE_CLK);

  /** Configure Alternate functionality in appropriate Control register
   *  - Pin Control Register n (PORTx_PCRn)
   *    Set the Pin Mux Control for Port A PCR1 and PCR2
   *      PTA1: UART0_RX (ALT2)
   *      PTA2: UART0_TX (ALT2)
   */
  PORTA_PCR1 |= PORT_PCR_MUX(PORTA_UART0_FUNC);
  PORTA_PCR2 |= PORT_PCR_MUX(PORTA_UART0_FUNC);
  }
