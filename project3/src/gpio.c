/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file gpio.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 7th, 2017
 * @brief This file contains definition of port assignment related functions
 */

#include "common_ccc.h"
#include "gpio.h"


/*---------------------------------------------------------------------------*/

#define ENABLE_CLK                (1)
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


