/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file circbuf.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 1, 2017
 * @brief Declarations for circular buffer functions.
 */

#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

/*---------------------------------------------------------------------------*/

/** Object: CB_t: Circular buffer type */
typedef struct
  {
  uint32_t  buf_size;  /* Buffer length */
  uint8_t  *buf_start; /* Buffer start */
  uint8_t  *buf_end;   /* Buffer end */
  uint32_t  count;     /* Content count */
  uint8_t  *head;      /* Content head */
  uint8_t  *tail;      /* Content tail */
  } CB_t;

/** Object: CB_status: Circular buffer status enumeration */
typedef enum
  {
    CB_SUCCESS,
    CB_NULL,
    CB_LENGTH,
    CB_BUFFER_FULL,
    CB_BUFFER_EMPTY,
    CB_ENOMEM
  } CB_status;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function CB_init() allocates Circular buffer.
 *
 * @param  cb - Circular buffer object
 * @param  length - Length of the buffer
 *
 * @return Circular buffer status enumeration
 */
CB_status CB_init(CB_t **cb, uint32_t length);

/**
 * @brief The function CB_destroy() deallocates Circular buffer.
 *
 * @param  cb - Circular buffer object
 *
 * @return Circular buffer status enumeration
 */
CB_status CB_destroy(CB_t *cb);

/**
 * @brief The function CB_buffer_add_item() adds a single value to the buffer.
 *
 * @param  cb - Circular buffer object
 * @param  data - Value to be added to the buffer
 *
 * @return Circular buffer status enumeration
 */
CB_status CB_buffer_add_item(CB_t *cb, uint8_t data);

/**
 * @brief The function CB_buffer_remove_item() removed a single value from the
 *        buffer.
 *
 * @param  cb - Circular buffer object
 * @param  data - Value removed from the buffer
 *
 * @return Circular buffer status enumeration
 */
CB_status CB_buffer_remove_item(CB_t *cb, uint8_t *data);

/**
 * @brief The function CB_is_full() tests if the Circular buffer is full.
 *
 * @param  cb - Circular buffer object
 *
 * @return Returns success if the Circular buffer is full.
 */
CB_status CB_is_full(CB_t *cb);

/**
 * @brief The function CB_is_empty() tests if the Circular buffer is full.
 *
 * @param  cb - Circular buffer object
 *
 * @return Returns success if the Circular buffer is empty.
 */
CB_status CB_is_empty(CB_t *cb);

/**
 * @brief The function CB_peek() returns the data value at a select index
 *        position.
 *
 * @param  cb - Circular buffer object
 * @param  index - Index position into the buffer
 * @param  data - Value from index position in the buffer
 *
 * @return Circular buffer status enumeration
 */
CB_status CB_peek(CB_t *cb, uint32_t index, uint8_t *data);

/**
 * @brief The function CB_length() returns the length of the buffer.
 *
 * @param  cb - Circular buffer object
 *
 * @return Length of the buffer
 */
static inline uint32_t CB_length(CB_t *cb)
  {
  return (NULL == cb) ? 0 : cb->buf_size;
  }

/**
 * @brief The function CB_count() returns number of data items in the buffer.
 *
 * @param  cb - Circular buffer object
 *
 * @return Data items in the buffer
 */
static inline uint32_t CB_count(CB_t *cb)
  {
  return (NULL == cb) ? 0 : cb->count;
  }

/*---------------------------------------------------------------------------*/

#endif /* __CIRCBUF_H__ */
