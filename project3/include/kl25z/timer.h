/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Program 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file uart.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 30, 2017
 * @brief This file contains declaration of timer related drivers.
 */

#ifndef __TIMER_H_
#define __TIMER_H_

/*---------------------------------------------------------------------------*/

/** Object: systick_rollover: Counter used to track the number of times that
 *          the SysTick counter has rolled over.
 */
extern volatile uint32_t systick_rollover;

/** Object: systick_rate: The duration in seconds of a single tick. */
double systick_rate;

/** Object: systick_rollover_rate: The duration in seconds for SysTick counter
 *          to rollover.
 */
double systick_rollover_rate;

/*---------------------------------------------------------------------------*/

/**
 * @brief This function initializes the board for timer usage.
 *
 * @param None
 * @return None
 */
void timer_board_init();

/*---------------------------------------------------------------------------*/

/**
 * @brief This function configures timer.
 *
 * @param None
 * @return None
 */
void timer_configure();

/*---------------------------------------------------------------------------*/

/**
 * @brief Reset the timer
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE void timer_reset(void)
  {
  SysTick->VAL = 0;
  systick_rollover = 0;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Read elapsed ticks
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t timer_ticks(void)
  {
  return SysTick_LOAD_RELOAD_Msk - SysTick->VAL;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Read SysTick rollover count
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t timer_rollovers(void)
  {
  return systick_rollover;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief SysTick elapsed ticks to seconds
 *
 * @param None
 * @return None
 */
__attribute__((always_inline)) __STATIC_INLINE double timer_elapsed(uint32_t ticks, uint32_t rollovers)
  {
  return (systick_rollover_rate * rollovers) + (systick_rate * ticks);
  }

/*---------------------------------------------------------------------------*/

#endif /* __TIMER_H_ */
