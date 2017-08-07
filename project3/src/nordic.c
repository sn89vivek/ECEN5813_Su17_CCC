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
 * @brief This file contains definitions for nordic drivers
 */

/*---------------------------------------------------------------------------*/

#include "common_ccc.h"

/*---------------------------------------------------------------------------*/

uint8_t nrf_read_register(uint8_t reg)
  {
  uint8_t status, data;
  NRF_CHIP_ENABLE();
  status = SPI_write_byte(NRF_READ_COMMAND + reg);
  data = SPI_read_byte();
  NRF_CHIP_DISABLE();
  return data;
  }

/*---------------------------------------------------------------------------*/

void nrf_write_register(uint8_t reg, uint8_t value)
  {
  uint8_t status;
  NRF_CHIP_ENABLE();
  status = SPI_write_byte(NRF_WRITE_COMMAND + reg);
  SPI_read_byte(status);
  SPI_write_byte(value);
  NRF_CHIP_DISABLE();
  }

/*---------------------------------------------------------------------------*/

void nrf_read_sequence(uint8_t reg, uint8_t *data, uint8_t len)
  {
  uint8_t status;
  NRF_CHIP_ENABLE();
  status = SPI_write_byte(NRF_READ_COMMAND + reg);
  while(len--)
    {
    SPI_read_byte(*data++);
    }
  NRF_CHIP_DISABLE();
  }

/*---------------------------------------------------------------------------*/

void nrf_write_sequence(uint8_t reg, uint8_t *data, uint8_t len)
  {
  uint8_t status;
  NRF_CHIP_ENABLE();
  status = SPI_write_byte(NRF_WRITE_COMMAND + reg);
  while(len--)
    {
	SPI_write_byte(*data++);
	/* Dummy read. reg used as dummy variable here */
    SPI_read_byte(reg);
    }
  NRF_CHIP_DISABLE();
  }

/*---------------------------------------------------------------------------*/

uint8_t nrf_read_status()
  {
  return(nrf_read_register(STATUS_REG));
  }

/*---------------------------------------------------------------------------*/

void nrf_write_config(uint8_t config)
  {
  nrf_write_register(CONFIG_REG, config);
  }

/*---------------------------------------------------------------------------*/

uint8_t nrf_read_config()
  {
  return(nrf_read_register(CONFIG_REG));
  }

/*---------------------------------------------------------------------------*/

uint8_t nrf_read_rf_setup()
  {
  return(nrf_read_register(RF_SETUP_REG));
  }

/*---------------------------------------------------------------------------*/

void nrf_write_rf_setup(uint8_t config)
  {
  nrf_write_register(RF_SETUP_REG, config);
  }

/*---------------------------------------------------------------------------*/

uint8_t nrf_read_rf_ch()
  {
  return(nrf_read_register(RF_CH_REG));
  }

/*---------------------------------------------------------------------------*/

void nrf_write_rf_ch(uint8_t channel)
  {
  nrf_write_register(RF_CH_REG, channel);
  }

/*---------------------------------------------------------------------------*/

void nrf_read_TX_ADDR(uint8_t *address)
  {
  nrf_read_sequence(TX_ADDR_REG, address, 5);
  }

/*---------------------------------------------------------------------------*/

void nrf_write_TX_ADDR(uint8_t *address)
  {
  nrf_write_sequence(TX_ADDR_REG, address, 5);
  }

/*---------------------------------------------------------------------------*/

uint8_t nrf_read_fifo_status()
  {
  return(nrf_read_register(FIFO_STATUS_REG));
  }

/*---------------------------------------------------------------------------*/

void nrf_flush_tx_fifo()
  {
  uint8_t status;
  NRF_CHIP_ENABLE();
  status = SPI_write_byte(FLUSH_TX_COMMAND);
  SPI_read_byte(status); /* dummy */
  NRF_CHIP_DISABLE();
  }

/*---------------------------------------------------------------------------*/

void nrf_flush_rx_fifo()
  {
  uint8_t status;
  NRF_CHIP_ENABLE();
  status = SPI_write_byte(FLUSH_RX_COMMAND);
  SPI_read_byte(status); /* dummy */
  NRF_CHIP_DISABLE();
  }

/*---------------------------------------------------------------------------*/

void nordic_test()
  {
  uint8_t status;
  status = nrf_read_status();
  status = nrf_read_config();
  nrf_write_config(0x55);
  status = nrf_read_config();
  status = nrf_read_rf_setup();
  nrf_write_rf_setup(0x05);
  status = nrf_read_rf_setup();
  nrf_write_rf_setup(0x0A);
  status = nrf_read_rf_setup();
  status = nrf_read_rf_ch();
  nrf_write_rf_ch(0x7F);
  status = nrf_read_rf_ch();
  status = nrf_read_fifo_status();
  }
