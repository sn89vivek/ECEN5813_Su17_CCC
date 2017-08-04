/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file led_kl25z.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 23 2017
 * @brief This file contains definition for on-board LED driver.
 */

#include "common_ccc.h"
#include "led_kl25z.h"

/*---------------------------------------------------------------------------*/

#define PORT_MUX_AS_GPIO  (1)

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void TPM1_IRQHandler();

/*---------------------------------------------------------------------------*/

void led_board_init(void)
  {
  /** Enable Clock to UART0 module
   *  - System Clock Gating Control Register 5 (SIM_SCGC5)
   *    Set bit 10 to enable clock gate to the PORTB module.
   */
  SIM->SCGC5 |= SIM_SCGC5_PORTB(1) | SIM_SCGC5_PORTB_MASK;
  }

/*---------------------------------------------------------------------------*/

void led_configure()
  {
  /** Configure Alternate functionality in appropriate Control register
   *  - Pin Control Register n (PORTx_PCRn)
   *    Set the Pin Mux Control for Port B PCR18
   */
  PORTB_PCR18 |= PORT_PCR_MUX(PORT_MUX_AS_GPIO);

  /** Set pin PTB18 as output
   *  - Port Data Direction Register (GPIOx_PDDR)
   *    Set pin PTB18 as output
   */
  PTB->PDDR = 1 << PTB18;

  /** Clear Red-LED
   *  - Port Clear Output Register (GPIOx_PCOR)
   *    Clear PTB18 of PDOR
   */
  PTB->PCOR = 1 << PTB18;
  }

/*---------------------------------------------------------------------------*/

void led_modulate()
  {
  /** Source of the internal slow reference clock is 32 kHz.
   *    32 kHz is 0.03125 ms
   *    50 ms is 1,600 x 0.03125 ms
   *      Prescale set to 'Divide by 1'
   *      Count up from zero
   *      Modulo 1,600
   */

  /** Setup a Multipurpose Clock Course (MCG) to drive the TMP1 interrupt.
   *  - MCG Control 1 Register (MCG_C1)
   *    Select the slow internal reference clock
   *    Enable the MCGIRCLK line
   */
  MCG->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;

  /** Gate the clock to TPM1
   *  - System Clock Gating Control Register 6 (SIM_SCGC6)
   *    Enable the TMP1 clock
   *
   * Note: Selected TPM1 because it is on Port B which is enabled for Red LED.
   */
  SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

  /** Select TPM clock source as MCGIRCLK
   *  - System Options Register 2 (SIM_SOPT2)
   */
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);

  /** Count up from zero
   *  - Counter (TPMx_CNT)
   */
  TPM1->CNT = 0;

  /** Overflow when counter value reaches the modulo value
   *  - Modulo (TPMx_MOD)
   */
  TPM1->MOD = 1600 & TPM_MOD_MOD_MASK;

  /**
   *  - Status and Control (TPMx_SC)
   *    LPTPM counter operates in up counting mode
   *    LPTPM counter increments on every LPTPM counter clock
   *    Prescale factor - Divide by 1
   *    Enable interrupt TPM1_IRQHandler
   */
  TPM1->SC = TPM_SC_CMOD(1) | TPM_SC_PS(0) | TPM_SC_TOIE_MASK;

  /** Enable interrupt TPM1_IRQHandler
   *  - Interrupt Set-Enable Register (NVIC_ISER)
   *    Enable interrupt TPM1_IRQHandler
   */
  NVIC_EnableIRQ(TPM1_IRQn);
  NVIC_SetPriority(TPM1_IRQn, 0);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief TPM1 Interrupt handler
 *
 * This ISR handles modulation of the red LED.
 *
 * @param none
 * @return none
 */
void TPM1_IRQHandler()
  {
  led_red_toggle();

  /** Clear the TPM0 overflow flag
   *  - Status and Control (TPMx_SC)
   *    Clear LPTPM overflow counter
   */
  TPM1->SC |= TPM_SC_TOF_MASK;
  }
