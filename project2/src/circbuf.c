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
 * @brief Definitions for circular buffer functions.
 */

#include "common_ccc.h"
#include "circbuf.h"
#include "memory.h"

/*---------------------------------------------------------------------------*/
/* Global variables */
CB_t *CB_tx, *CB_rx;

/*---------------------------------------------------------------------------*/

CB_status CB_init(CB_t **cb, uint32_t length)
  {
  CB_status status;

  if (NULL == cb)
    {
    status = CB_NULL;
    }
  else if (length <= 1 || (length & (length - 1)) != 0)
    {
    status = CB_LENGTH;
    }
  else
    {
    *cb = (CB_t*)reserve_words(SIZEOF_IN_WORDS(CB_t));
    if (NULL == *cb)
      {
      status = CB_ENOMEM;
      }
    else
      {
      (*cb)->buf_start = (uint8_t*)reserve_words(LENGTH_IN_WORDS(length));
      if (NULL == (*cb)->buf_start)
        {
        status = CB_ENOMEM;
        }
      else
        {
        (*cb)->buf_end = (*cb)->buf_start + length - 1;
        (*cb)->head = (*cb)->buf_start;
        (*cb)->tail = (*cb)->buf_start;
        (*cb)->buf_size = length;
        (*cb)->count = 0;
        status = CB_SUCCESS;
        }
      }
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

CB_status CB_destroy(CB_t *cb)
  {
  CB_status status;

  if (NULL == cb)
    {
    status = CB_NULL;
    }
  else
    {
    free_words((uint32_t*)cb->buf_start);
    free_words((uint32_t*)cb);
    status = CB_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

CB_status CB_buffer_add_item(CB_t *cb, uint8_t data)
  {
  CB_status status;

  if (NULL == cb)
    {
    status = CB_NULL;
    }
  else if (cb->buf_size == cb->count)
    {
    status = CB_BUFFER_FULL;
    }
  else
    {
    /* Add item to end of buffer with wrapping at bounds of memory */
    *(cb->tail) = data;
    cb->tail = (cb->tail < cb->buf_end) ? cb->tail + 1 : cb->buf_start;

#ifdef __ATOMIC__
    __ATOMIC_START();
#endif
    cb->count++;
#ifdef __ATOMIC__
    __ATOMIC_END();
#endif

    status = CB_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

CB_status CB_buffer_remove_item(CB_t *cb, uint8_t *data)
  {
  CB_status status;

  if (NULL == cb || NULL == data)
    {
    status = CB_NULL;
    }
  else if (0 == cb->count)
    {
    status = CB_BUFFER_EMPTY;
    }
  else
    {
    /* Remove item from front of buffer with wrapping at bounds of memory */
    *data = *(cb->head);
    cb->head = (cb->head < cb->buf_end) ? cb->head + 1 : cb->buf_start;
    __ATOMIC_START();

#ifdef __ATOMIC__
    __ATOMIC_START();
#endif
    cb->count--;
#ifdef __ATOMIC__
    __ATOMIC_END();
#endif

    __ATOMIC_END();
    status = CB_SUCCESS;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

CB_status CB_is_full(CB_t *cb)
  {
  CB_status status;

  if (NULL == cb)
    {
    status = CB_NULL;
    }
  else
    {
    status = (cb->buf_size == cb->count) ? CB_SUCCESS : CB_LENGTH;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

CB_status CB_is_empty(CB_t *cb)
  {
  CB_status status;

  if (NULL == cb)
    {
    status = CB_NULL;
    }
  else
    {
    status = (0 == cb->count) ? CB_SUCCESS : CB_LENGTH;
    }

  return status;
  }

/*---------------------------------------------------------------------------*/

CB_status CB_peek(CB_t *cb, uint32_t index, uint8_t *data)
  {
  CB_status status;

  if (NULL == cb || NULL == data)
    {
    status = CB_NULL;
    }
  else if (index >= cb->count)
    {
    status = CB_LENGTH;
    }
  else
    {
    /* Does the buffer wrap past the end of the memory block? */
    if (cb->head < cb->tail)
      /* The buffer doesn't wrap past the end of the memory block. */
      {
      *data = *(cb->head + index);
      }
    else
      /* The buffer wraps past the end of the memory block. */
      {
      /* Are we indexing into segment of buffer at end of memory? */
      if (cb->head + index <= cb->buf_end)
        /* We are indexing into segment of buffer at end of memory. */
  {
  *data = *(cb->head + index);
  }
      else
        /* We are indexing into segment of buffer at beginning of memory. */
  {
  const uint8_t segment_length = cb->tail - cb->buf_start;
  const uint8_t segment_index = index - (cb->count - segment_length);
        *data = *(cb->buf_start + segment_index);
  }
      }
    status = SUCCESS;
    }

  return status;
  }
