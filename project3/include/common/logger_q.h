/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file logger_q.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 4, 2017
 * @brief Declarations for logger queue related functions.
 */

#ifndef __LOGGER_Q_H__
#define __LOGGER_Q_H__

/*---------------------------------------------------------------------------*/

/** Object: logger_id_t: Logger ids to indicate the log context */
typedef enum
  {
  LOGGER_INITIALIZED,     // No Payload
  GPIO_INITIALIZED,       // No Payload
  SYSTEM_INITIALIZED,     // No Payload
  SYSTEM_HALTED,          // No Payload
  INFO,                   // Send important info with regards to an info string
  WARNING,                // Send important info with regards to an info string
  ERROR,                  // Send important info with regards to an info string
  PROFILING_STARTED,      // Profiling analysis has started
  PROFILING_RESULT,       // Log a function id and a count for how long it took
  PROFILING_COMPLETED,    // Profiling analysis has completed
  DATA_RECEIVED,          // An item was received on UART, transmits it back
  DATA_ANALYSIS_STARTED,  // No Payload
  DATA_ALPHA_COUNT,       // Log number of alphabetic characters
  DATA_NUMERIC_COUNT,     // Log number of alphabetic characters
  DATA_PUNCTUATION_COUNT, // Log number of alphabetic characters
  DATA_MISC_COUNT,        // Log number of alphabetic characters
  DATA_ANALYSIS_COMPLETED // No Payload
  } logger_id_t;

/** Object: logger_item_t: Logger item structure */
typedef struct
  {
  logger_id_t  id;
  uint32_t     timestamp;
  uint8_t     *data;
  uint32_t     length;
  } logger_item_t;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_q_init() initializes logger_q.
 *
 * @param  None
 *
 * @return None
 */
#ifdef VERBOSE
void log_q_init(void);
#else
#define log_q_init()
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_item() takes a pointer to a log item structure and
 *        logs the content without blocking.
 *
 * @param  item - Log item structure
 *
 * @return logger_q_e
 */
#ifdef VERBOSE
void log_item(const logger_item_t * const item);
#else
#define log_item()
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_item() takes a pointer to a log item structure and
 *        logs the content without blocking.
 *
 * @param  item - Log item structure
 *
 * @return logger_q_e
 */
#ifdef VERBOSE
#define log_id1(id)                                                           \
  {                                                                           \
  const logger_item_t item = { (id), 0, NULL, 0 };                            \
  log_item(&item);                                                            \
  }
#define log_id2(id, ptr, len)                                                 \
  {                                                                           \
  const logger_item_t item = { (id), 0, (ptr), (len) };                       \
  log_item(&item);                                                            \
  }
#endif

/*---------------------------------------------------------------------------*/

#endif /* __LOGGER_Q_H__ */
