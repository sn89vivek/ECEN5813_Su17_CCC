/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file nordic.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 5, 2017
 * @brief This file contains declarations for nordic drivers
 */

#ifndef INCLUDES_NORDIC_H_
#define INCLUDES_NORDIC_H_

#include "nordic_reg.h"
#include "spi_kl25z.h"

/*---------------------------------------------------------------------------*/

#define NRF_CHIP_ENABLE()            SS0_LOW()
#define NRF_CHIP_DISABLE()           SS0_HIGH()
#define FLUSH_TX_COMMAND             (0xE1)
#define FLUSH_RX_COMMAND             (0xE2)

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads an nrf register over SPI and returns its value
 *
 * @param  reg: Address of the register to be read
 *
 * @return Value of the register
 */
uint8_t nrf_read_register(uint8_t reg);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes a value over SPI to nrf register
 *
 * @param  reg Address of the register to be written to
 * @param value Value to be written to the register
 *
 * @return None
 */
void nrf_write_register(uint8_t reg, uint8_t value);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the sequence of bytes from a specifed register
 *
 * @param reg: Register to be read from
 * @param data: pointer to buffer where the read sequnce of bytes will be stored
 * @param len: length of sequence
 *
 * @return None
 */
void nrf_read_sequence(uint8_t reg, uint8_t *data, uint8_t len);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes a sequence of bytes from a specifed register
 *
 * @param reg: Register to be written to.
 * @param data: pointer to buffer where the write sequnce of bytes is stored
 * @param len: length of sequence
 *
 * @return None
 */
void nrf_write_sequence(uint8_t reg, uint8_t *data, uint8_t len);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the value of nrf status register
 *
 * @param None
 *
 * @return Value read from status register
 */
uint8_t nrf_read_status();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes a value to config register
 *
 * @param config: Value to be written to config register
 *
 * @return None
 */
void nrf_write_config(uint8_t config);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the config register value
 *
 * @param None
 *
 * @return Value read from the config register
 */
uint8_t nrf_read_config();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the rf_setup register value
 *
 * @param None
 *
 * @return Value read from rf setup register
 */
uint8_t nrf_read_rf_setup();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes a value to the rf_setup register
 *
 * @param config: Value to be written to rf setup register
 *
 * @return None
 */
void nrf_write_rf_setup(uint8_t config);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the current channel
 *
 * @param None
 *
 * @return Value read from rf channel register
 */
uint8_t nrf_read_rf_ch();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes a value to the rf_ch register
 *
 * @param channel: Value to be written to rf channel register
 *
 * @return None
 */
void nrf_write_rf_ch(uint8_t channel);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the 5 bytes of the TX_ADDR register
 *
 * @param pointer to where the TX_ADDR data will be stored
 *
 * @return None
 */
void nrf_read_TX_ADDR(uint8_t *address);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes the 5 bytes to the TX_ADDR register
 *
 * @param pointer to where data to be written is stored
 *
 * @return None
 */
void nrf_write_TX_ADDR(uint8_t *address);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads the fifo status register of nrf
 *
 * @param None
 *
 * @return Value read from register
 */
uint8_t nrf_read_fifo_status();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function sends command to nrf to flush TX_FIFO
 *
 * @param None
 *
 * @return None
 */
void nrf_flush_tx_fifo();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function sends command to nrf to flush RX_FIFO
 *
 * @param None
 *
 * @return None
 */
void nrf_flush_rx_fifo();

/*---------------------------------------------------------------------------*/

void nordic_test();

#endif /* INCLUDES_NORDIC_H_ */
