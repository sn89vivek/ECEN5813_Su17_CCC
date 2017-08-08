/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file rtc_kl25z.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 5, 2017
 * @brief Definitions for RTC related functions.
 */

#include "common_ccc.h"
#include "rtc_kl25z.h"
#include "logger.h"

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void RTC_Seconds_IRQHandler();
uint32_t timestamp = 0;

/*---------------------------------------------------------------------------*/

void rtc_board_init(void)
  {
  /** Select 32K system oscillator
   *  - System Options Register 1 (SIM_SOPT1)
   */
  SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;

  /** Setup RTC clock gating
   *  - System Clock Gating Control Register 6 (SIM_SCGC6)
   *    Enable RTC access and interrupts
   */
  SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;
  }

/*---------------------------------------------------------------------------*/

void rtc_configure()
  {
  /** Reset RTC registers
   *  - RTC Control Register (RTC_CR)
   */
  RTC->CR = RTC_CR_SWR_MASK;
  RTC->CR &= ~RTC_CR_SWR_MASK;

  /** Enable 32.768 kHz oscillator
   *  - RTC Control Register (RTC_CR)
   */
  RTC->CR |= RTC_CR_OSCE(1);

  /* delay for oscilattor to settle */
  for(uint32_t i = 50000; i != 0; i--) {}

  /** Enable seconds interrupt
   *  - RTC Interrupt Enable Register (RTC_IER)
   */
  RTC->IER |= RTC_IER_TSIE(1);

  /* Write to TSR register to clear TIF flag */
  RTC->TSR = 0;

  /* Enable RTC
   * - Write 1 to TCE bit of SR
   */
  RTC->SR = RTC_SR_TCE_MASK;

  /** Enable interrupt RTC_Seconds_IRQHandler
   *  - Interrupt Set-Enable Register (NVIC_ISER)
   *    Enable interrupt RTC_Seconds_IRQHandler
   */
  NVIC_EnableIRQ(RTC_Seconds_IRQn);
  NVIC_SetPriority(RTC_Seconds_IRQn, 0);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief RTC Seconds Interrupt handler
 *
 * This ISR handles 1s clock processing.
 *
 * @param none
 * @return none
 */
void RTC_Seconds_IRQHandler()
  {
  timestamp = RTC->TSR;
  log_item(HEARTBEAT);
  }
