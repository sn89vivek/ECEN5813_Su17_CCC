/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file spi_kl25z.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 7th, 2017
 * @brief This file contains declaration of spi drivers
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_


/*---------------------------------------------------------------------------*/

#define PORT4              (4)

/*---------------------------------------------------------------------------*/

/**
 * @brief The function initializes the SPI gpio
 *
 * @param  None
 *
 * @return None
 */
void GPIO_nrf_init();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function initializes the SPI module
 *
 * @param  None
 *
 * @return None
 */
void spi_configure();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function reads a byte over SPI. It block until the byte read.
 *
 * @param  None
 *
 * @return Byte read
 */
uint8_t SPI_read_byte();

/*---------------------------------------------------------------------------*/

/**
 * @brief The function writes a byte to SPI. It block until the byte written.
 *
 * @param  byte: Byte to be writte over SPI
 *
 * @return None
 */
uint8_t SPI_write_byte(uint8_t byte);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function initializes sends a packet of specified length over SPI
 *
 * @param  p: Pointer the packet array
 * @param length: Length of the packet in bytes
 *
 * @return None
 */
void SPI_send_packet(uint8_t *p, size_t length);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function flushes the SPI buffers. (Waits until SPI buffer is empty)
 *
 * @param  None
 *
 * @return None
 */
void SPI_flush();

/*---------------------------------------------------------------------------*/

#define SS0_LOW()                       (GPIOC_PCOR = (1) << PORT4)
#define SS0_HIGH()                      (GPIOC_PSOR = (1) << PORT4)

#endif /* INCLUDES_SPI_H_ */
