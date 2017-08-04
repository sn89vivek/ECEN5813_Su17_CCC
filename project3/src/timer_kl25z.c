/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file timer_kl25z.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 30 2017
 * @brief This file contains definition of timer related drivers.
 */

#include "common_ccc.h"
#include "timer_kl25z.h"

/*---------------------------------------------------------------------------*/

volatile uint32_t systick_rollover;

double systick_rate;

double systick_rollover_rate;

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void SysTick_Handler();

/*---------------------------------------------------------------------------*/

void timer_board_init(void)
  {
  /** Enable interrupt TPM1_IRQHandler
   *  - Interrupt Set-Enable Register (NVIC_ISER)
   *    Enable interrupt TPM1_IRQHandler
   *    Set to max priority
   */
  NVIC_EnableIRQ(SysTick_IRQn);
  NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
  }

/*---------------------------------------------------------------------------*/

void timer_configure()
  {
  /** Set the SysTimer reload value to max
   *  - SysTick Reload Value Register (SYST_RVR)
   */
  SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;

  /** Clear the current counter value
   *  - SysTick Current Value Register (SYST_CVR)
   */
  SysTick->VAL = 0;

  /** Clear the rollover counter */
  systick_rollover = 0;

  /** Compute the SysTick rate based on the SystemCoreClock */
  systick_rate = 1 / (double)SystemCoreClock;

  /** Compute the SysTick rollover rate based on the SystemCoreClock and the
   *  SysTick reload register value.
   */
  systick_rollover_rate = systick_rate * SysTick_LOAD_RELOAD_Msk;

  /**
   *  - SysTick Control and Status Register (SYST_CSR)
   *    Enable counter
   *    Enable SysTick interrupt when counter reaches zero
   *    SysTick uses processor clock
   */
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief SysTick Interrupt handler
 *
 * This ISR handles processing every SysTick interval.
 *
 * @param none
 * @return none
 */
void SysTick_Handler()
  {
  systick_rollover++;
  }
