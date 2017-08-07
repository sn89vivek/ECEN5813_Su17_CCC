/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file gpio.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 7th, 2017
 * @brief This file contains declaration of port assignment related functions
 */

#ifndef INCLUDES_GPIO_H_
#define INCLUDES_GPIO_H_

/*---------------------------------------------------------------------------*/

#define PORT4                     (4)

/*---------------------------------------------------------------------------*/

/**
 * @brief The function initializes ports for nrf chip
 *
 * @param  None
 *
 * @return None
 */
void GPIO_nrf_init();

/*---------------------------------------------------------------------------*/

#endif /* INCLUDES_GPIO_H_ */
