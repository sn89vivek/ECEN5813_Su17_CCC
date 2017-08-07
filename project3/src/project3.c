/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project3.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 22, 2017
 * @brief This file contains definition of project3 related tasks
 */

#if defined(PROJECT3)

#include <string.h>
#include "common_ccc.h"
#include "project3.h"
#include "board.h"
#include "logger.h"

#if defined(PLATFORM_HOST)

void project3()
  {
  log_item(SYSTEM_INITIALIZED);

  log_item(SYSTEM_HALTED);
  }

#elif defined(PLATFORM_BBB)

void project3()
  {
  log_item(SYSTEM_INITIALIZED);

  log_item(SYSTEM_HALTED);
  }

#elif defined(PLATFORM_MKL)

#include "led_kl25z.h"
#include "memory_dma.h"

/*---------------------------------------------------------------------------*/
/* Global variables                                                          */


/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

bool_t parse_rx(metrics_t *metrics);
bool_t update_metrics(metrics_t *metrics, uint8_t character);
void reset_rx_metrics(metrics_t *metrics);
void log_rx_metrics(metrics_t *metrics);

/*---------------------------------------------------------------------------*/

/**
 * @brief Function parse_rx() parses the Rx input.
 *
 * @param metrics: pointer to the metrics_t object
 *
 * @return True denotes parsing is complete
 */
bool_t parse_rx(metrics_t *metrics)
  {
  bool_t result;

  result = FALSE;
  while (FALSE == result && CB_SUCCESS != CB_is_empty(logger_rx))
    {
    uint8_t next_char;
    if (CB_SUCCESS == CB_buffer_remove_item(logger_rx, &next_char))
      result = update_metrics(metrics, next_char);
    }
  return result;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Function update_metrics() updates the Rx metrics.
 *
 * @param metrics: pointer to the metrics_t object
 * @param character: next character of the sequence
 *
 * @return True denotes parsing is complete
 */
bool_t update_metrics(metrics_t *metrics, uint8_t character)
  {
  bool_t result;

  result = FALSE;
  metrics->total++;
  if (isalpha(character))
    metrics->alpha++;
  else if (isdigit(character))
    metrics->numeric++;
  else if (ispunct(character))
    metrics->punct++;
  else if ('\r' == character)
    {
    metrics->misc++;
    result = TRUE;
    }
  else
    {
    metrics->misc++;
    }
  return result;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Function reset_rx_metrics() resets the Rx metrics.
 *
 * @param metrics: pointer to the metrics_t object
 *
 * @return None
 */
void reset_rx_metrics(metrics_t *metrics)
  {
  metrics->alpha = 0;
  metrics->numeric = 0;
  metrics->punct = 0;
  metrics->misc = 0;
  metrics->total = 0;
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Function log_rx_metrics() logs the Rx metrics.
 *
 * @param metrics: pointer to the metrics_t object
 *
 * @return None
 */
void log_rx_metrics(metrics_t *metrics)
  {
  log_string("Process metrics...\r\n");
  log_item(DATA_ANALYSIS_STARTED);
  log_item2(DATA_ALPHA_COUNT, metrics->alpha);
  log_item2(DATA_NUMERIC_COUNT, metrics->numeric);
  log_item2(DATA_PUNCTUATION_COUNT, metrics->punct);
  log_item2(DATA_MISC_COUNT, metrics->misc);
  log_item(DATA_ANALYSIS_COMPLETED);
  reset_rx_metrics(metrics);
  }

/*---------------------------------------------------------------------------*/

void project3()
  {
  board_init();

  log_string("Hello World\n");

  /* Modulate the Red LED at 50% duty cycle */
  led_modulate();

  log_item(SYSTEM_INITIALIZED);

  log_string("DMA memory tests...\r\n");
  dma_memory_tests();

  metrics_t metrics;
  reset_rx_metrics(&metrics);

  log_string("Nordic test...\r\n");
  nordic_test();

  log_string("Enter data at the console.\r\n");
  while (1)
    {
    if (TRUE == parse_rx(&metrics))
      log_rx_metrics(&metrics);
    }

  log_item(SYSTEM_HALTED);
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */

#endif /* PROJECT3 */
