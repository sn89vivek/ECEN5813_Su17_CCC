/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Program 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file rtc.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 6, 2017
 * @brief This file contains declaration of RTC related drivers.
 */

#ifndef __RTC_H_
#define __RTC_H_

/*---------------------------------------------------------------------------*/

/**
 * @brief This function initializes the board for rtc usage.
 *
 * @param None
 * @return None
 */
void rtc_board_init();

/*---------------------------------------------------------------------------*/

/**
 * @brief This function configures rtc.
 *
 * @param None
 * @return None
 */
void rtc_configure();

/*---------------------------------------------------------------------------*/

/**
 * @brief Get seconds since start of epoch
 *
 * @param None
 * @return Seconds
 */
__attribute__((always_inline)) static inline time_t rtc_now(void)
  {
  return time(NULL);
  }

/*---------------------------------------------------------------------------*/

#endif /* __RTC_H_ */
