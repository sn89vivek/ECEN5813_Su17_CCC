/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file logger.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date August 3, 2017
 * @brief Declarations for logger related functions.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

/*---------------------------------------------------------------------------*/

#define MAX_LOGGER_LEN    (0x100)
#define MAX_LOGGER_Q_LEN  (0x100)

#define LOGGER_ITEM_DATA_LEN  (8)

/*---------------------------------------------------------------------------*/

/** Object: logger_id_t: Logger ids to indicate the log context */
typedef enum
  {
  HEARTBEAT,              // No Payload
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
  logger_id_t id;
  uint32_t    timestamp;
  uint8_t     length;
  uint8_t     data[LOGGER_ITEM_DATA_LEN];
  } logger_item_t;

/*---------------------------------------------------------------------------*/

#include "circbuf.h"
#include "logger_q.h"

/*---------------------------------------------------------------------------*/

/** Object: logger_rx: Logger Rx circular buffer */
extern CB_t *logger_rx;

/** Object: logger_tx: Logger Tx circular buffer */
extern CB_t *logger_tx;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_init() initializes logger.
 *
 * @param  None
 *
 * @return None
 */
#ifdef VERBOSE
void log_init(void);
#else
#define log_init()
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_data() takes a pointer to data and logs length
 *        number of raw bytes.
 *
 * @param  data - Start address of data
 * @param  length - Number of bytes to log
 *
 * @return None
 */
#ifdef VERBOSE
void log_data(const uint8_t * const data,
              const size_t length);
#else
#define log_data(data, length)
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_string() takes a pointer to a z-string and logs
 *        characters up to the \0 character.
 *
 * @param  str - Start address of z-string
 *
 * @return None
 */
#ifdef VERBOSE
void log_string(const char8_t * const str);
#else
#define log_string(str)
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_integer() takes an integer value and logs the base
 *        10 character representation.
 *
 * @param  value - Integer value to be logged
 *
 * @return None
 */
#ifdef VERBOSE
void log_integer(const int32_t value);
#else
#define log_integer(value)
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_flush() blocks until the current log buffer is
 *        empty.
 *
 * @param  None
 *
 * @return None
 */
#ifdef VERBOSE
void log_flush();
#else
#define log_flush()
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_item() takes content to log without blocking.
 *
 * @param  id - Logger id
 *
 * @return None
 */
#ifdef VERBOSE
void log_item(const logger_id_t id);
#else
#define log_item(id)
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_item2() takes content to log without blocking.
 *
 * @param  id - Logger id
 * @param  value - Number value
 *
 * @return None
 */
#ifdef VERBOSE
void log_item2(const logger_id_t id,
               const uint32_t value);
#else
#define log_item2(id, value)
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief The function log_item3() takes content to log without blocking.
 *
 * @param  id - Logger id
 * @param  data - Start of data
 * @param  length - Size of data
 *
 * @return None
 */
#ifdef VERBOSE
void log_item3(const logger_id_t id,
               const uint8_t * const data,
               const uint8_t length);
#else
#define log_item3(id, data, length)
#endif

/*---------------------------------------------------------------------------*/

#endif /* __LOGGER_H__ */
