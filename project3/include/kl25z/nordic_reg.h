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
 * @brief This file contains declarations for nordic registers and bitmasks
 */

#ifndef INCLUDES_NORDIC_REG_H_
#define INCLUDES_NORDIC_REG_H_

/*---------------------------------------------------------------------------*/

#define NRF_READ_COMMAND                   (0x00)
#define NRF_WRITE_COMMAND                  (0x20)

/* CONFIG registers and corresponding bitmasks */
#define CONFIG_REG                         (0x00)

#define CONFIG_MASK_RX_DR_SHIFT            (6)
#define CONFIG_MASK_RX_DR_MASK             (0x40)
#define CONFIG_MASK_TX_DS_SHIFT            (5)
#define CONFIG_MASK_TX_DS_MASK             (0x20)
#define CONFIG_MASK_MAX_RT_SHIFT           (4)
#define CONFIG_MASK_MAX_RT_MASK            (0x10)
#define CONFIG_EN_CRC_SHIFT                (3)
#define CONFIG_EN_CRC_MASK                 (0x08)
#define CONFIG_CRCO_SHIFT                  (2)
#define CONFIG_CRCO_MASK                   (0x04)
#define CONFIG_PWR_UP_SHIFT                (1)
#define CONFIG_PWR_UP_MASK                 (0x02)
#define CONFIG_PRIM_RX_SHIFT               (0)
#define CONFIG_PRIM_RX_MASK                (0x01)

/* STATUS registers and corresponding bitmasks */
#define STATUS_REG                         (0x07)

#define STATUS_RX_DR_SHIFT                 (6)
#define STATUS_RX_DR_MASK                  (0x40)
#define STATUS_TX_DS_SHIFT                 (5)
#define STATUS_TX_DS_MASK                  (0x20)
#define STATUS_MAX_RT_SHIFT                (4)
#define STATUS_MAX_RT_MASK                 (0x10)
#define STATUS_RX_P_NO_SHIFT               (1)
#define STATUS_RX_P_NO_MASK                (0x0E)
#define STATUS_TX_FULL_SHIFT               (0)
#define STATUS_TX_FULL_MASK                (0x01)

/* RF_SETUP registers and corresponding bitmasks */
#define RF_SETUP_REG                       (0x06)

#define RF_SETUP_PLL_LOCK_SHIFT            (4)
#define RF_SETUP_PLL_LOCK_MASK             (0x10)
#define RF_SETUP_RF_DR_SHIFT               (3)
#define RF_SETUP_RF_DR_MASK                (0x08)
#define RF_SETUP_RF_PWR_SHIFT              (1)
#define RF_SETUP_RF_PWR__MASK              (0x06)
#define RF_SETUP_LNA_HCURR_SHIFT           (0)
#define RF_SETUP_LNA_HCURR_MASK            (0x01)

/* RF_CH registers and corresponding bitmasks */
#define RF_CH_REG                          (0x05)

#define RF_CH_SHIFT                        (0)
#define RF_CH_MASK                         (0x3F)

/* FIFO_STATUS registers and corresponding bitmasks */
#define FIFO_STATUS_REG                    (0x17)

#define FIFO_STATUS_TX_REUSE_SHIFT         (6)
#define FIFO_STATUS_TX_REUSE_MASK          (0x40)
#define FIFO_STATUS_TX_FULL_SHIFT          (5)
#define FIFO_STATUS_TX_FULL_MASK           (0x20)
#define FIFO_STATUS_TX_EMPTY_SHIFT         (4)
#define FIFO_STATUS_TX_EMPTY_MASK          (0x10)
#define FIFO_STATUS_RX_FULL_SHIFT          (1)
#define FIFO_STATUS_RX_FULL_MASK           (0x02)
#define FIFO_STATUS_RX_EMPTY_SHIFT         (0)
#define FIFO_STATUS_RX_EMPTY_MASK          (0x01)

/* TX_ADDR register */
#define TX_ADDR_REG                        (0x10)

#endif /* INCLUDES_NORDIC_REG_H_ */
