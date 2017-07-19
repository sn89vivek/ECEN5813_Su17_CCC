/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
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

#ifndef UART_H_
#define UART_H_

/*---------------------------------------------------------------------------*/
/* UART0 configuration                                                       */

/* UART0 Baud Rate */
#define UART0_BAUD_RATE			  115200

/* UART0 clock source: MCGFLLCLK/2 */
#define CLK_SRC_MCGPLLCLK_2       (1)

/* Enable Clock */
#define ENABLE_CLK                (1)

/* Diable Clock */
#define DISABLE_CLK               (0)

/* Disable UART0 Interrupts
 *  - UART Control Register 2 (UARTx_C2)
 *    Set all of the interrupt bits to disabled.
 *    Set Rx and Tx to normal operation.
 */
#define DISABLE_UART0()			  (UART0->C2 = 0)

/* Enable UART0 Interrupts
 *  - UART Control Register 2 (UARTx_C2)
 *    Enable the UART0 Rx and Tx interrupts.
 */
#define ENABLE_UART0()            (UART0->C2 |= UART0_C2_RE(RECEIVE_ENABLE) + UART0_C2_TE(TRANSMIT_ENABLE))

/* Stop Bits */
#define ONE_STOP_BIT              (0)
#define TWO_STOP_BIT              (1)

/* Compute the prescale divisor for UART0 baud rate */
#define UART_OSR_VAL			  (4)
#define UART0_BAUD_RATE_REG_VAL   (SystemCoreClock / (UART_OSR_VAL * UART0_BAUD_RATE))
#define UART0_BAUD_REG_HIGH       ((UART0_BAUD_RATE_REG_VAL >> 8) & 0x0F)
#define UART0_BAUD_REG_LOW        (UART0_BAUD_RATE_REG_VAL & 0xFF)

#define PORTA_UART0_FUNC          (2)
#define TRANSMIT_ENABLE           (1)
#define RECEIVE_ENABLE            (1)
#define RECEIVE_INTERRUPT_ENABLE  (1)

#define UART0_DISABLE_TIE()       (UART0->C2 &= ~(UART0_C2_TIE_MASK))
#define UART0_ENABLE_TIE()        (UART0->C2 |= (UART0_C2_TIE_MASK))
#define UART0_TIE_ENABLED()       (UART0->C2 & UART0_C2_TIE_MASK)

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

#endif /* UART_H_ */
