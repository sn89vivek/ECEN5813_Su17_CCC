/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file uart.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 5, 2017
 * @brief This file contains declaration of uart related drivers.
 */

#ifndef __UART_H_
#define __UART_H_

/*---------------------------------------------------------------------------*/

/*
 * @brief This function configures UART peripheral
 *
 * @param None
 * @return None
 *
 */
void uart_configure();

/*---------------------------------------------------------------------------*/

/*
 * @brief This function configures interrupts for the UART peripheral
 *
 * @param None
 * @return None
 *
 */
void uart_interrupts_enable();

/*---------------------------------------------------------------------------*/

/*
 * @brief This function transmits a buffer of specified size over UART
 *
 * @param buf: pointer to the buffer to be transimitted
 * @param n: No. of bytes to be transmitted over UART
 * @return Operation status (SUCCESS or FAILURE)
 *
 */
uint8_t uart_send_n(const uint8_t *buf, uint32_t n);

/*---------------------------------------------------------------------------*/

/*
 * @brief This function transmits a byte over UART
 *
 * @param data: pointer to the data to be transmitted
 * @return Operation status (SUCCESS or FAILURE)
 *
 */
uint8_t uart_send(const uint8_t *data);

/*
 * @brief This function receives a buffer of specified size over UART
 *
 * @param buf: pointer to the buffer to store received bytes
 * @param n: No. of bytes to be received over UART
 * @return Operation status (SUCCESS or FAILURE)
 *
 */
uint8_t uart_receive_n(uint8_t *buf, uint32_t n);

/*---------------------------------------------------------------------------*/

/*
 * @brief This function receives a byte over UART
 *
 * @param data: pointer to the data where received variable is stored
 * @return Operation status (SUCCESS or FAILURE)
 *
 */
uint8_t uart_receive(uint8_t *data);

/*---------------------------------------------------------------------------*/

/*
 * @brief This function prints a constant string over uart using blocking
 *        uart transmit.
 *
 * @param strng: string to be transmitted
 * @return none
 *
 */
void uart_print_string(const uint8_t *strng);

/*---------------------------------------------------------------------------*/

#endif /* __UART_H_ */
