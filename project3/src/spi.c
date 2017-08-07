/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file spi.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 7th, 2017
 * @brief This file contains definitions of SPI drivers
 */


#include "common_ccc.h"
#include "spi.h"

/*---------------------------------------------------------------------------*/
/* SPI configuration                                                       */
#define ENABLE_CLK                (1)
#define DISABLE_CLK               (0)
#define ENABLE_SPI0()             (SPI0->C1 |= (SPI_C1_SPE_MASK))
#define DISABLE_SPI0()            (SPI0->C1 &= ~(SPI_C1_SPE_MASK))
#define SPI_MASTER                (1)
#define SPI_TRANSFER_ON_EDGE      (1)

/*---------------------------------------------------------------------------*/

void SPI_init()
  {
  GPIO_nrf_init();

  /* Enable Clock to SPI0 module   */
  SIM->SCGC4 |= SIM_SCGC4_SPI0(ENABLE_CLK);

  /** Disable SPI0 before setting configuration */
  DISABLE_SPI0();

  /* Set the prescale divisor for SPI0
   *
   * Baud rate = SystemCoreClock/(SPPR * SPR)
   * 1.09MHz = 20.09MHz/(5*4)
   *
   * SPPR_reg_value = SPPR-1
   * SPR_reg_value = (log SPR)-1
   *                    2
   */
  SPI0->BR = SPI_BR_SPPR(4) | SPI_BR_SPR(1);

  /* Set SPI0 features
   *    SPI interrupts disabled
   *    SPI master
   *    Clock polarity: Active high (Idle low)
   *    Clock Phase: Transfer on rising edge
   *    SS under GPIO control
   *    Transfer with MSB first
   */
  SPI0->C1 = SPI_C1_MSTR(SPI_MASTER) + SPI_C1_CPHA(0);

  /* Enable UART0 */
  ENABLE_SPI0();
  }

/*---------------------------------------------------------------------------*/

uint8_t SPI_read_byte()
  {
  /* wait till tx buffer not empty */
  while(!(SPI0->S & SPI_S_SPTEF_MASK)) {}
  SPI0->D = 0xFF; /* Dummy */
  /* Wait till rx buffer empty */
  while(!(SPI0->S & SPI_S_SPRF_MASK)) {}
  return (SPI0->D);
  }

/*---------------------------------------------------------------------------*/

uint8_t SPI_write_byte(uint8_t byte)
  {
  /* wait till tx buffer not empty */
  while(!(SPI0->S & SPI_S_SPTEF_MASK)) {}
  SPI0->D = byte;
  /* Wait till rx buffer empty */
  while(!(SPI0->S & SPI_S_SPRF_MASK)) {}
  return (SPI0->D);  /* dummy read */
  }

/*---------------------------------------------------------------------------*/

void SPI_send_packet(uint8_t *p, size_t length)
  {
  while (length--)
    {
	SPI_write_byte(*p++);
    }
  }

/*---------------------------------------------------------------------------*/

void SPI_flush()
  {
  /* wait till tx buffer not empty */
  while(!(SPI0->S & SPI_S_SPTEF_MASK)) {}
  }

/*---------------------------------------------------------------------------*/
