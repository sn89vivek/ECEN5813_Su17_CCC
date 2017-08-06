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

/** Object: LOGQ_t: Circular buffer type */
typedef struct
  {
  uint32_t       buf_size;  /* Buffer length */
  logger_item_t *buf_start; /* Buffer start */
  logger_item_t *buf_end;   /* Buffer end */
  uint32_t       count;     /* Content count */
  logger_item_t *head;      /* Content head */
  logger_item_t *tail;      /* Content tail */
  } LOGQ_t;

/** Object: LOGQ_status: Circular buffer status enumeration */
typedef enum
  {
    LOGQ_SUCCESS,
    LOGQ_NULL,
    LOGQ_LENGTH,
    LOGQ_BUFFER_FULL,
    LOGQ_BUFFER_EMPTY,
    LOGQ_ENOMEM
  } LOGQ_status;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function LOGQ_init() allocates Circular buffer.
 *
 * @param  length - Length of the buffer
 *
 * @return Circular buffer status enumeration
 */
LOGQ_status LOGQ_init(uint32_t length);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function LOGQ_destroy() deallocates Circular buffer.
 *
 * @param  None
 *
 * @return Circular buffer status enumeration
 */
LOGQ_status LOGQ_destroy(void);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function LOGQ_add_item() adds a single log item to the buffer.
 *
 * @param  item - Log item to be added
 *
 * @return Circular buffer status enumeration
 */
LOGQ_status LOGQ_add_item(logger_item_t *item);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function LOGQ_remove_item() removed a single log item from the
 *        buffer.
 *
 * @param  item - Log item removed
 *
 * @return Circular buffer status enumeration
 */
LOGQ_status LOGQ_remove_item(logger_item_t *item);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function LOGQ_is_full() tests if the Circular buffer is full.
 *
 * @param  None
 *
 * @return Returns success if the Circular buffer is full.
 */
LOGQ_status LOGQ_is_full(void);

/*---------------------------------------------------------------------------*/

/**
 * @brief The function LOGQ_is_empty() tests if the Circular buffer is full.
 *
 * @param  None
 *
 * @return Returns success if the Circular buffer is empty.
 */
LOGQ_status LOGQ_is_empty(void);

/*---------------------------------------------------------------------------*/

#endif /* __LOGGER_Q_H__ */
