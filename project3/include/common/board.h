/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file board.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 23, 2017
 * @brief This file contains declaration of board startup.
 */

#ifndef __BOARD_H_
#define __BOARD_H_

/*---------------------------------------------------------------------------*/

/** Object: board_is_ready: Indicates that the board is ready to be used. */
extern bool_t board_is_ready;

/*---------------------------------------------------------------------------*/

/**
 * @brief This function provides a central location to initialize clocks,
 *        ports and configure devices.
 *
 * @param None
 * @return None
 *
 */
void board_init(void);

/*---------------------------------------------------------------------------*/

#endif /* __BOARD_H_ */
