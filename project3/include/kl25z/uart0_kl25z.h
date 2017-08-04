/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file uart0_kl25z.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 5, 2017
 * @brief This file contains declaration of uart related drivers.
 */

#ifndef __UART0_KL25Z_H_
#define __UART0_KL25Z_H_

/*---------------------------------------------------------------------------*/

#define UART0_DISABLE_TIE()       (UART0->C2 &= ~(UART0_C2_TIE_MASK))
#define UART0_ENABLE_TIE()        (UART0->C2 |= (UART0_C2_TIE_MASK))
#define UART0_TIE_ENABLED()       (UART0->C2 & UART0_C2_TIE_MASK)

/*---------------------------------------------------------------------------*/

/*
 * @brief This function initializes the port of UART0
 *
 * @param None
 * @return None
 */
void uart_board_init();

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

#endif /* __UART0_KL25Z_H_ */
