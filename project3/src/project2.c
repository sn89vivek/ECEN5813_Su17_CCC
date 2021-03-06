/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
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

#if defined(PROJECT2)

#include <string.h>
#include "common_ccc.h"
#include "project2.h"
#include "circbuf.h"
#include "conversion.h"

#if defined(PLATFORM_HOST)

void project2()
  {
  }

#elif defined(PLATFORM_BBB)

#include "board.h"

void project2()
  {
  }

#elif defined(PLATFORM_MKL)

#include "uart0_kl25z.h"
#include "board.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */

/** Object: CB_tx: Tx circular buffer for UART */
CB_t *CB_tx;

/** Object: CB_rx: Rx circular buffer for UART */
CB_t *CB_rx;

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void UART0_IRQHandler();
uint32_t put_zstring(CB_t *cb, const char8_t *str);
uint32_t put_string(const uint8_t *str, uint32_t length, CB_t *cb);
void proj2_err(proj2_status pr_status, CB_status cb_status);
proj2_status input_sequence_parse(CB_t *cb, proj2_statistics_t *stats);
proj2_status update_statistics(proj2_statistics_t *stats, uint8_t character);
void initialize_statistics(proj2_statistics_t *stats);
void dump_statistics(proj2_statistics_t *stats, CB_t *cb);

/*---------------------------------------------------------------------------*/

/**
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
  if ((UART0->S1 & UART0_S1_TDRE_MASK) && (UART0_TIE_ENABLED()))
    {
    /* Check if this is the last character */
    if (CB_count(CB_tx) == 1)
      UART0_DISABLE_TIE();
    status = CB_buffer_remove_item(CB_tx, &uart_char);
    if (status != CB_SUCCESS)
      proj2_err(PR_TXBUF_REMOVE_FAILED, status);
    uart_send((const uint8_t *)&uart_char);
    }

  /* Rx Interrupt */
  if (UART0->S1 & UART0_S1_RDRF_MASK)
    {
    uart_receive(&uart_char);
    status = CB_buffer_add_item(CB_rx, uart_char);
    if (status != CB_SUCCESS)
      proj2_err(PR_RXBUF_ADD_FAILED, status);
    }
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Function put_zstring() pushes a string into tx buffer and initiates
 *        a write sequence over UART.
 *
 * @param cb - Pointer to Tx circular buffer
 * @param str - Null terminated string
 *
 * @return Number of bytes written to the buffer
 */
uint32_t put_zstring(CB_t *cb, const char8_t *str)
  {
  return put_string((const uint8_t *)str, (uint32_t)strlen(str), cb);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief This function handles pushes a string into tx buffer and initiates a
 *        write sequence over UART
 *
 * @note The length of the string must be passed explicitly. This function
 *       does not look for termination character in the string
 *
 * @note If buffer is full, this function waits till slots open in buffer.
 *
 * @warning If @p length is greater than MAX_CB_LENGTH, this function will
 *          never return. length must always be less that MAX_CB_LENGTH. This
 *          condition is not enforced by the function.
 *
 * @param str: Pointer to the string to be written
 * @param length: length of the string to be written
 * @param cb: Pointer to tx Circular buffer
 *
 * @return num_buffer of bytes written to the buffer
 */
uint32_t put_string(const uint8_t *str, uint32_t length, CB_t *cb)
  {
  uint32_t bytes_written = 0;

  if (str != NULL)
    {
    while (bytes_written < length)
      {
      CB_status status = CB_buffer_add_item(cb, *str);
      switch (status)
        {
        case CB_BUFFER_FULL:
          continue;
        case CB_SUCCESS:
          bytes_written++;
          str++;
          break;
        default:
          proj2_err(PR_TXBUF_ADD_FAILED, status);
          break;
        }
      }
    }

  if (bytes_written != 0)
    UART0_ENABLE_TIE();

  return bytes_written;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief This function handles the errors generated in project2
 *
 * This function handles errors for project2. Uart interrupts are disabled and
 * error is printed out to terminal using blocking uart transmit functions.
 * After printing error, any cleanup if required needs to be performed and
 * then the function blocks forever.
 *
 * @param pr_status: Project related status enumeration
 * @param cb_status: Circular buffer related status enumeration
 *
 * @return This function does not return
 */
void proj2_err(proj2_status pr_status, CB_status cb_status)
  {
  /* disable interrupts. Not supported anymore */
  uint8_t errcode[4];
  __disable_irq();
  uart_print_string((const uint8_t*)"\r\nFatal Error occurred...\r\n");
  uart_print_string((const uint8_t*)"Project 2 Error code: ");
  my_itoa((int32_t)pr_status, errcode, 10);
  uart_print_string((const uint8_t*)errcode);
  uart_print_string((const uint8_t*)"\r\nCB Error code: ");
  my_itoa((int32_t)cb_status, errcode, 10);
  uart_print_string((const uint8_t*)errcode);
  uart_print_string((const uint8_t*)"\r\n");

  /* TODO perform any cleanup if required */
  while (1) {}
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief This function parses the input string sequence as per project 2
 *        requirements
 *
 * @param cb: pointer to rx buffer
 * @param stats: pointer to the proj2_statistics_t object
 *
 * @return proj2_status enumneration to denote parsing complete/incomplete
 */
proj2_status input_sequence_parse(CB_t *cb, proj2_statistics_t *stats)
  {
  CB_status status;
  proj2_status result;
  uint8_t next_char;

  result = PR_PARSING_IN_PROGRESS;

  while (CB_is_empty(cb) != CB_SUCCESS)
    {
    status = CB_buffer_remove_item(cb, &next_char);
    if (status != CB_SUCCESS)
      proj2_err(PR_RXBUF_REMOVE_FAILED, status);
    result = update_statistics(stats, next_char);
    if (result == PR_PARSING_COMPLETE)
      break;
    }
  return result;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief This function updates input sequence statistics as per project 2
 *        requirements
 *
 * @param stats: pointer to the proj2_statistics_t object
 * @param character: next character of the sequence
 *
 * @return proj2_status enumneration to denote parsing complete/incomplete
 */
proj2_status update_statistics(proj2_statistics_t *stats, uint8_t character)
  {
  proj2_status result;

  result = PR_PARSING_IN_PROGRESS;
  stats->num_total++;
  if (isalpha(character))
    stats->num_alpha++;
  else if (isdigit(character))
    stats->num_numeric++;
  else if (ispunct(character))
    stats->num_punct++;
  else if (character == '\r')
    {
    stats->num_misc++;
    result = PR_PARSING_COMPLETE;
    }
  else
    {
    stats->num_misc++;
    }
   return result;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief This function initialises the statistics variable
 *
 * @param stats: pointer to the proj2_statistics_t object
 *
 * @return none
 */
void initialize_statistics(proj2_statistics_t *stats)
  {
  stats->num_total = 0;
  stats->num_alpha = 0;
  stats->num_numeric = 0;
  stats->num_punct = 0;
  stats->num_misc = 0;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief This function dumps the project 2 statistics into tx buffer alongwith
 *        helpful messages
 *
 * @param stats: pointer to the proj2_statistics_t object
 * @param cb: pointer to tx buffer
 *
 * @return none
 */
void dump_statistics(proj2_statistics_t *stats, CB_t *cb)
  {
  char8_t num_buffer[11+1];

  put_zstring(cb, "\r\n****** PROJECT 2 INPUT SEQUENCE STATISTICS ******\r\n");

  put_zstring(cb, "\r\nNumber of alphabetic characters:      ");
  my_itoa(stats->num_alpha, (uint8_t *)num_buffer, 10);
  put_zstring(cb, num_buffer);

  put_zstring(cb, "\r\nNumber of numeric characters:         ");
  my_itoa(stats->num_numeric, (uint8_t *)num_buffer, 10);
  put_zstring(cb, num_buffer);

  put_zstring(cb, "\r\nNumber of punctuation characters:     ");
  my_itoa(stats->num_punct, (uint8_t *)num_buffer, 10);
  put_zstring(cb, num_buffer);

  put_zstring(cb, "\r\nNumber of miscellaneous characters:   ");
  my_itoa(stats->num_misc, (uint8_t *)num_buffer, 10);
  put_zstring(cb, num_buffer);

  put_zstring(cb, "\r\nTotal characters received:            ");
  my_itoa(stats->num_total, (uint8_t *)num_buffer, 10);
  put_zstring(cb, num_buffer);

  put_zstring(cb, "\r\n");

  initialize_statistics(stats);
  }

/*---------------------------------------------------------------------------*/

void project2()
  {
  CB_status status;
  proj2_statistics_t sequence_stats;

  /* Create Tx buffers */
  status = CB_init(&CB_tx, MAX_CB_LENGTH);
  if (status != CB_SUCCESS)
    proj2_err(PR_TXBUF_CREATION_FAILED, status);

  /* Create Rx buffer */
  status = CB_init(&CB_rx, MAX_CB_LENGTH);
  if (status != CB_SUCCESS)
    proj2_err(PR_RXBUF_CREATION_FAILED, status);

  board_init();

  put_zstring(CB_tx, "Hello UART\r\n");
  put_zstring(CB_tx, "Does UART-buffer integration work?\r\n");
  initialize_statistics(&sequence_stats);
  while (1)
    {
    if (input_sequence_parse(CB_rx, &sequence_stats) == PR_PARSING_COMPLETE)
      dump_statistics(&sequence_stats, CB_tx);
    }
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */

#endif /* PROJECT2 */
