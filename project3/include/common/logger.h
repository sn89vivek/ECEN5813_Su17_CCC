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
#define log_data()
#endif

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
#define log_string()
#endif

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
#define log_integer()
#endif

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

#endif /* __LOGGER_H__ */
