/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project2.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 15, 2017
 * @brief This file contains definition of project2 related tasks
 */

#include "common_ccc.h"
#include "circbuf.h"
#include "project2.h"

#if defined(PLATFORM_HOST) || defined(PLATFORM_BBB) 

void project2()
  {
  }

#elif defined(PLATFORM_MKL)

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */
void UART0_IRQHandler();
uint32_t put_string(const uint8_t *str, uint32_t length, CB_t *cb);
void proj2_err(proj2_status pr_stat, CB_status cb_stat);

/*---------------------------------------------------------------------------*/

/*
 * @brief UART0 Interrupt handler
 *
 * This ISR handles transmission and reception of UART characters from
 * respective tx and rx circular buffers
 *
 * @note Unsuccessful CB operations result in a blocking fault
 * @param none
 *
 * @return none
 */
void UART0_IRQHandler()
  {
  uint8_t uart_char;
  CB_status status;

  /* Check and Process UART interrupt */

  /* Tx Interrupt */
  if(UART0->S1 & UART0_S1_TDRE_MASK)
    {
  /* Check if this is the last character */
  if(CB_count(CB_tx) == 1)
    UART0_DISABLE_TIE();
  status = CB_buffer_remove_item(CB_tx, &uart_char);
  if(status != CB_SUCCESS)
    proj2_err(PR_TXBUF_REMOVE_FAILED, status);
  UART0->D = uart_char;
    }

  /* Rx Interrupt */
  if(UART0->S1 & UART0_S1_RDRF_MASK)
    {
  uart_receive(&uart_char);
  status = CB_buffer_add_item(CB_rx, uart_char);
  if(status != CB_SUCCESS)
    proj2_err(PR_RXBUF_ADD_FAILED, status);
    }
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief This function handles pushes a string into tx buffer and initiates a
 *        write sequence over UART
 *
 * @note The length of the string must be passed explicitly. This function
 *       does not look for termination character in the string
 *
 * @param str: Pointer to the string to be written
 * @param length: Lenth of the string to be written
 * @param cb: Poinet to tx Circular buffer
 *
 * @return Number of bytes written to the buffer
 */
uint32_t put_string(const uint8_t *str, uint32_t length, CB_t *cb)
  {
  CB_status status;
  uint32_t bytes_written = 0;

  if(str != NULL)
    {
    while(bytes_written < length)
    {
    status = CB_buffer_add_item(cb, *str++);
    if(status == CB_SUCCESS)
      bytes_written++;
    else if(status == CB_BUFFER_FULL)
      break;
    else
    proj2_err(PR_TXBUF_ADD_FAILED, status);
    }
    }
  if(bytes_written != 0)
    UART0_ENABLE_TIE();
  return bytes_written;
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief This function handles the errors generated in project2
 *
 * This function handles errors for project2. Uart interrupts are disabled and
 * error is printed out to terminal using blocking uart transmit functions.
 * After printing error, any cleanup if required needs to be performed and
 * then the function blocks forever.
 *
 * @param pr_stat: Project related status flag
 * @param cb_stat: Circular buffer related status flag
 *
 * @return This function does not return
 */
void proj2_err(proj2_status pr_stat, CB_status cb_stat)
  {
  // TODO
  while(1) {}
  }

/*---------------------------------------------------------------------------*/

void project2()
  {
  CB_status status;

  /* Create Tx buffers */
  status = CB_init(&CB_tx, MAX_CB_LENGTH);
  if(status != CB_SUCCESS)
    proj2_err(PR_TXBUF_CREATION_FAILED, status);

  /* Create Rx buffer */
  status = CB_init(&CB_rx, MAX_CB_LENGTH);
  if(status != CB_SUCCESS)
    proj2_err(PR_RXBUF_CREATION_FAILED, status);

  uart_configure();
  uart_interrupts_enable();
  put_string((const uint8_t *)"Does UART-buffer integration work?\r\n", 36, CB_tx);
  while(1) {}
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */
