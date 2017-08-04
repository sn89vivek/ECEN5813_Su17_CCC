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
 * @brief The function log_data() takes a pointer to memory and logs length
 *        number of raw bytes.
 *
 * @param  data - Start address of data to be logged
 * @param  length - Number of bytes to log
 *
 * @return None
 */
#ifdef VERBOSE
void log_data(uint8_t *data, size_t length);
#else
#define log_data()
#endif

/**
 * @brief The function log_string() takes a pointer to memory and logs length
 *        number of characters.
 *
 * @param  str - Start address of string to be logged
 * @param  length - Number of bytes to log
 *
 * @return None
 */
#ifdef VERBOSE
void log_string(char8_t *str, size_t length);
#else
#define log_string()
#endif

/**
 * @brief The function log_zstring() takes a pointer to memory and logs
 *        characters up to the \0 character.
 *
 * @param  str - Start address of z-string to be logged
 *
 * @return None
 */
#ifdef VERBOSE
void log_zstring(char8_t *str);
#else
#define log_zstring()
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
void log_integer(int32_t value);
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
