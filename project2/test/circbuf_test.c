/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file circbuf_test.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 2, 2017
 * @brief This file validates the circbuf functions.
 */

#include "common_ccc.h"
#include "circbuf.h"

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_init(), validate arg 'cb' with invalid value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_init__1(void **state)
  {
  assert_int_equal(CB_init(NULL, 0), CB_NULL);
  }

/**
 * @brief For function CB_init(), validate arg 'length' with invalid value 0.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_init__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 0), CB_LENGTH);
  }

/**
 * @brief For function CB_init(), validate arg 'length' with invalid value 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_init__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 1), CB_LENGTH);
  }

/**
 * @brief For function CB_init(), validate arg 'length' with valid value 2.
 *        Validate state variables.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_init__4(void **state)
  {
  CB_t *cb;
  uint32_t length = 2;
  assert_int_equal(CB_init(&cb, length), CB_SUCCESS);

  /* Primary sanity test of buffer state */
  assert_int_not_equal(cb->buf_start, NULL);
  assert_int_not_equal(cb->buf_end, NULL);
  assert_int_not_equal(cb->head, NULL);
  assert_int_not_equal(cb->tail, NULL);
  assert_int_equal(cb->buf_size, length);
  assert_int_equal(cb->count, 0);

  /* Secondary sanity test of buffer state */
  assert_int_equal(cb->buf_end, cb->buf_start + length - 1);
  assert_int_equal(cb->head, cb->buf_start);
  assert_int_equal(cb->tail, cb->buf_start);
  assert_int_equal(cb->buf_size, length);
  }

/**
 * @brief For function CB_init(), validate arg 'length' with invalid value 3.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_init__5(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 3), CB_LENGTH);
  }

/**
 * @brief For function CB_init(), validate arg 'length' with valid value 4.
 *        Validate state variables.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_init__6(void **state)
  {
  CB_t *cb;
  uint32_t length = 4;
  assert_int_equal(CB_init(&cb, length), CB_SUCCESS);

  /* Primary sanity test of buffer state */
  assert_int_not_equal(cb->buf_start, NULL);
  assert_int_not_equal(cb->buf_end, NULL);
  assert_int_not_equal(cb->head, NULL);
  assert_int_not_equal(cb->tail, NULL);
  assert_int_equal(cb->buf_size, length);
  assert_int_equal(cb->count, 0);

  /* Secondary sanity test of buffer state */
  assert_int_equal(cb->buf_end, cb->buf_start + length - 1);
  assert_int_equal(cb->head, cb->buf_start);
  assert_int_equal(cb->tail, cb->buf_start);
  assert_int_equal(cb->buf_size, length);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_destroy(), validate arg 'cb' with invalid value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_destroy__1(void **state)
  {
  assert_int_equal(CB_destroy(NULL), CB_NULL);
  }

/**
 * @brief For function CB_destroy(), validate arg 'cb' with valid buffer
 *        pointer.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_destroy__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_destroy(cb), CB_SUCCESS);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_buffer_add_item(), validate arg 'cb' with invalid
 *        value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_add_item__1(void **state)
  {
  assert_int_equal(CB_buffer_add_item(NULL, 0), CB_NULL);
  }

/**
 * @brief For function CB_buffer_add_item(), validate adding 1 data item to
 *        a buffer that holds 2 items.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_add_item__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  }

/**
 * @brief For function CB_buffer_add_item(), validate adding 2 data items to
 *        a buffer that holds 2 items.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_add_item__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  }

/**
 * @brief For function CB_buffer_add_item(), validate adding 3 data items to
 *        a buffer that holds 2 items.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_add_item__4(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_BUFFER_FULL);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_buffer_remove_item(), validate arg 'cb' with invalid
 *        value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_remove_item__1(void **state)
  {
  assert_int_equal(CB_buffer_remove_item(NULL, NULL), CB_NULL);
  }

/**
 * @brief For function CB_buffer_remove_item(), validate arg 'data' with
 *        invalid value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_remove_item__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, NULL), CB_NULL);
  }

/**
 * @brief For function CB_buffer_remove_item(), validate removal of 1 item from
 *        empty buffer.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_remove_item__3(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_BUFFER_EMPTY);
  }

/**
 * @brief For function CB_buffer_remove_item(), validate removal of 1 item from
 *        buffer with 1 item.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_buffer_remove_item__4(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_BUFFER_EMPTY);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_is_full(), validate arg 'cb' with invalid value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_full__1(void **state)
  {
  assert_int_equal(CB_is_full(NULL), CB_NULL);
  }

/**
 * @brief For function CB_is_full(), validate that an empty buffer is not
 *        reported as full.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_full__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_is_full(cb), CB_LENGTH);
  }

/**
 * @brief For function CB_is_full(), validate that a partially filled buffer is
 *        not reported as full.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_full__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_is_full(cb), CB_LENGTH);
  }

/**
 * @brief For function CB_is_full(), validate that a full buffer is reported as
 *        full.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_full__4(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_is_full(cb), CB_SUCCESS);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_is_empty(), validate arg 'cb' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_empty__1(void **state)
  {
  assert_int_equal(CB_is_empty(NULL), CB_NULL);
  }

/**
 * @brief For function CB_is_empty(), validate that an empty buffer is reported
 *        as empty.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_empty__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_is_empty(cb), CB_SUCCESS);
  }

/**
 * @brief For function CB_is_empty(), validate that a buffer that is partly
 *        filled is reported as not empty.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_is_empty__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_is_empty(cb), CB_LENGTH);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function CB_peek(), validate arg 'cb' with invalid value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_peek__1(void **state)
  {
  assert_int_equal(CB_peek(NULL, 0, NULL), CB_NULL);
  }

/**
 * @brief For function CB_peek(), validate arg 'data' with invalid value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_peek__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_peek(cb, 0, NULL), CB_NULL);
  }

/**
 * @brief For function CB_peek(), validate arg 'length' with an empty buffer.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_peek__3(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_peek(cb, 0, &data), CB_LENGTH);
  }

/**
 * @brief For function CB_peek(), validate seeking into a buffer with one
 *        entry.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_peek__4(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_peek(cb, 0, &data), CB_SUCCESS);
  assert_int_equal(CB_peek(cb, 1, &data), CB_LENGTH);
  }

/**
 * @brief For function CB_peek(), validate seeking into a buffer with multiple
 *        entries.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_peek__5(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 8), CB_SUCCESS);

  /* Add 7 entries into buffer */
  for (uint8_t i = 0; i < 7; i++)
    {
    assert_int_equal(CB_buffer_add_item(cb, i + 13), CB_SUCCESS);
    }

  /* Validate value of 7 entries in the buffer */
  for (uint8_t i = 0; i < 7; i++)
    {
    assert_int_equal(CB_peek(cb, i, &data), CB_SUCCESS);
    assert_int_equal(data, i + 13);
    }

  /* Validate peeking past end of buffer returns an error */
  assert_int_equal(CB_peek(cb, 7, &data), CB_LENGTH);

  /* Remove 6 entries from the buffer */
  for (uint8_t i = 0; i < 6; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i + 13);
    }

  /* Add 5 entries into buffer */
  for (uint8_t i = 0; i < 5; i++)
    {
    assert_int_equal(CB_buffer_add_item(cb, i + 33), CB_SUCCESS);
    }

  /* Validate value of 5 entries in the buffer */
  for (uint8_t i = 0; i < 8; i++)
    {
    switch (i)
      {
      case 0:
        assert_int_equal(CB_peek(cb, i, &data), CB_SUCCESS);
        assert_int_equal(data, i + 19);
        break;
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        assert_int_equal(CB_peek(cb, i, &data), CB_SUCCESS);
        assert_int_equal(data, i + 32);
        break;
      default:
        assert_int_equal(CB_peek(cb, i, &data), CB_LENGTH);
        break;
      }
    }

  /* Remove 3 entries from the buffer */
  for (uint8_t i = 0; i < 3; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i < 1 ? i + 19 : i + 32);
    }

  /* Validate value of 5 entries in the buffer */
  for (uint8_t i = 0; i < 8; i++)
    {
    switch (i)
      {
      case 0:
      case 1:
      case 2:
        assert_int_equal(CB_peek(cb, i, &data), CB_SUCCESS);
        assert_int_equal(data, i + 35);
        break;
      default:
        assert_int_equal(CB_peek(cb, i, &data), CB_LENGTH);
        break;
      }
    }

  /* Validate peeking past end of buffer returns an error */
  assert_int_equal(CB_peek(cb, 7, &data), CB_LENGTH);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief Validate wrapping data with a simple pattern of adding and removing
 *        items from buffer.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_sanity__1(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0xEE), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0xDD), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
  assert_int_equal(data, 0xEE);
  assert_int_equal(CB_buffer_add_item(cb, 0xCC), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0xBB), CB_BUFFER_FULL);
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
  assert_int_equal(data, 0xDD);
  assert_int_equal(CB_buffer_add_item(cb, 0xBB), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0xAA), CB_BUFFER_FULL);
  }

/**
 * @brief Validate wrapping data with a simple pattern of adding and removing
 *        items from buffer.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void CB_sanity__2(void **state)
  {
  CB_t *cb;
  uint8_t data;
  uint16_t i;
  assert_int_equal(CB_init(&cb, 32), CB_SUCCESS);

  /* Fill buffer */
  for (i = 0; i < 32; i++)
    {
    assert_int_equal(CB_buffer_add_item(cb, i), CB_SUCCESS);
    }
  assert_int_equal(CB_buffer_add_item(cb, i), CB_BUFFER_FULL);

  /* Remove and Add entries 32 times */
  for ( ; i < 64; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i - 32);

    assert_int_equal(CB_buffer_add_item(cb, i), CB_SUCCESS);
    }

  /* Remove-only entries 7 times to create a gap */
  for ( ; i < 71; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i - 32);
    }

  /* Add and Remove entries 25 times up to removal gap */
  for ( ; i < 96; i++)
    {
    assert_int_equal(CB_buffer_add_item(cb, i), CB_SUCCESS);

    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i - 32);
    }

  /* Add and Remove entries 160 times */
  for ( ; i < 256; i++)
    {
    assert_int_equal(CB_buffer_add_item(cb, i), CB_SUCCESS);

    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i - 25);
    }

  /* Empty buffer */
  for (i = 0; i < 25; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i + 231);
    }
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_BUFFER_EMPTY);
  }

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
  {
  const struct CMUnitTest tests[] =
    {
    unit_test(CB_init__1),
    unit_test(CB_init__2),
    unit_test(CB_init__3),
    unit_test(CB_init__4),
    unit_test(CB_init__5),
    unit_test(CB_init__6),
    unit_test(CB_destroy__1),
    unit_test(CB_destroy__2),
    unit_test(CB_buffer_add_item__1),
    unit_test(CB_buffer_add_item__2),
    unit_test(CB_buffer_add_item__3),
    unit_test(CB_buffer_add_item__4),
    unit_test(CB_buffer_remove_item__1),
    unit_test(CB_buffer_remove_item__2),
    unit_test(CB_buffer_remove_item__3),
    unit_test(CB_buffer_remove_item__4),
    unit_test(CB_is_full__1),
    unit_test(CB_is_full__2),
    unit_test(CB_is_full__3),
    unit_test(CB_is_full__4),
    unit_test(CB_is_empty__1),
    unit_test(CB_is_empty__2),
    unit_test(CB_is_empty__3),
    unit_test(CB_peek__1),
    unit_test(CB_peek__2),
    unit_test(CB_peek__3),
    unit_test(CB_peek__4),
    unit_test(CB_peek__5),
    unit_test(CB_sanity__1),
    unit_test(CB_sanity__2)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
