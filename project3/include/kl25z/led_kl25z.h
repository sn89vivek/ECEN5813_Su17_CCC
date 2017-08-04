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
 * @date July 23, 2017
 * @brief This file contains declaration for on-board LED driver.
 */

#ifndef __LED_KL25Z_H_
#define __LED_KL25Z_H_

/*---------------------------------------------------------------------------*/

#define PTB18  (18)

/*---------------------------------------------------------------------------*/

/**
 * @brief This function initializes the board for LED usage.
 *
 * @param None
 * @return None
 */
void led_board_init();

/*---------------------------------------------------------------------------*/

/**
 * @brief This function configures LED.
 *
 * @param None
 * @return None
 */
void led_configure();

/*---------------------------------------------------------------------------*/

/**
 * @brief Set Red-LED OFF
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE void led_red_off(void)
  {
  PTB->PCOR = 1 << PTB18;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Set Red-LED ON
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE void led_red_on(void)
  {
  PTB->PSOR = 1 << PTB18;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Toggle Red-LED
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE void led_red_toggle(void)
  {
  PTB->PTOR = 1 << PTB18;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Modulate the Red-LED at a 50msec.
 *
 * @param None
 * @return None
 */
void led_modulate();

/*---------------------------------------------------------------------------*/

#endif /* __LED_KL25Z_H_ */
