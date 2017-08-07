/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file spi_kl25z.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 7th, 2017
 * @brief This file contains definitions of SPI drivers
 */


#include "common_ccc.h"
#include "spi_kl25z.h"

/*---------------------------------------------------------------------------*/
/* SPI configuration                                                       */
#define ENABLE_CLK                (1)
#define DISABLE_CLK               (0)
#define ENABLE_SPI0()             (SPI0->C1 |= (SPI_C1_SPE_MASK))
#define DISABLE_SPI0()            (SPI0->C1 &= ~(SPI_C1_SPE_MASK))
#define SPI_MASTER                (1)
#define SPI_TRANSFER_ON_EDGE      (1)

#define PORTC_SPI0_FUNC           (2)
#define GPIO_FUNC                 (1)
#define OUTPUT_DIRECTION          (1)

/*---------------------------------------------------------------------------*/

void GPIO_nrf_init()
  {
  /* Enable clock to PortC */
  SIM->SCGC5 |= SIM_SCGC5_PORTC(ENABLE_CLK);

  /** Configure Alternate functionality in appropriate Control register
   *  - Pin Control Register n (PORTx_PCRn)
   *      PTC5: SPI0_SCK  (ALT2)
   *      PTC6: SPI0_MOSI (ALT2)
   *      PTC7: SPI0_MISO (ALT2)
   */
  PORTC_PCR5 |= PORT_PCR_MUX(PORTC_SPI0_FUNC);
  PORTC_PCR6 |= PORT_PCR_MUX(PORTC_SPI0_FUNC);
  PORTC_PCR7 = PORT_PCR_MUX(PORTC_SPI0_FUNC) + PORT_PCR_PE(1) + PORT_PCR_PS(1);


  /* Port PTC4: General purpose output for Chip select */
    /* Set functionality as GPIO from port control register */
  PORTC_PCR4 |= PORT_PCR_MUX(GPIO_FUNC);
    /* Configure direction using port data direction register */
  GPIOC_PDDR |= (OUTPUT_DIRECTION) << PORT4;

  /* Set initial value of port to 0 */
  GPIOC_PCOR |= (1) << PORT4;
  }

/*---------------------------------------------------------------------------*/

void spi_configure()
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
