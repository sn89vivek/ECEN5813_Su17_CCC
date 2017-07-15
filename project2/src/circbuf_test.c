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
#include <stdio.h>
#include "common_ccc.h"
#include "circbuf.h"

/*---------------------------------------------------------------------------*/

void CB_init__1(void **state)
  {
  assert_int_equal(CB_init(NULL, 0), CB_NULL);
  }

void CB_init__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 0), CB_LENGTH);
  }

void CB_init__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 1), CB_LENGTH);
  }

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

void CB_init__5(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 3), CB_LENGTH);
  }

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

void CB_destroy__1(void **state)
  {
  assert_int_equal(CB_destroy(NULL), CB_NULL);
  }

void CB_destroy__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_destroy(cb), CB_SUCCESS);
  }

/*---------------------------------------------------------------------------*/

void CB_buffer_add_item__1(void **state)
  {
  assert_int_equal(CB_buffer_add_item(NULL, 0), CB_NULL);
  }

void CB_buffer_add_item__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(NULL, 0), CB_NULL);
  }

void CB_buffer_add_item__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  }

void CB_buffer_add_item__4(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_BUFFER_FULL);
  }

/*---------------------------------------------------------------------------*/

void CB_buffer_remove_item__1(void **state)
  {
  assert_int_equal(CB_buffer_remove_item(NULL, NULL), CB_NULL);
  }

void CB_buffer_remove_item__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, NULL), CB_NULL);
  }

void CB_buffer_remove_item__3(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_remove_item(cb, &data), CB_BUFFER_EMPTY);
  }

/*---------------------------------------------------------------------------*/

void CB_is_full__1(void **state)
  {
  assert_int_equal(CB_is_full(NULL), CB_NULL);
  }

void CB_is_full__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_is_full(cb), CB_LENGTH);
  }

void CB_is_full__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_is_full(cb), CB_LENGTH);
  }

void CB_is_full__4(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_is_full(cb), CB_SUCCESS);
  }

/*---------------------------------------------------------------------------*/

void CB_is_empty__1(void **state)
  {
  assert_int_equal(CB_is_empty(NULL), CB_NULL);
  }

void CB_is_empty__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_is_empty(cb), CB_SUCCESS);
  }

void CB_is_empty__3(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_buffer_add_item(cb, 0), CB_SUCCESS);
  assert_int_equal(CB_is_empty(cb), CB_LENGTH);
  }

/*---------------------------------------------------------------------------*/

void CB_peek__1(void **state)
  {
  assert_int_equal(CB_peek(NULL, 0, NULL), CB_NULL);
  }

void CB_peek__2(void **state)
  {
  CB_t *cb;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_peek(cb, 0, NULL), CB_NULL);
  }

void CB_peek__3(void **state)
  {
  CB_t *cb;
  uint8_t data;
  assert_int_equal(CB_init(&cb, 2), CB_SUCCESS);
  assert_int_equal(CB_peek(cb, 0, &data), CB_LENGTH);
  }

/*---------------------------------------------------------------------------*/

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

  /* Remove and Add entries 224 times */
  for ( ; i < 256; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i - 32);

    assert_int_equal(CB_buffer_add_item(cb, i), CB_SUCCESS);
    }

  /* Empty buffer */
  for (i = 0; i < 32; i++)
    {
    assert_int_equal(CB_buffer_remove_item(cb, &data), CB_SUCCESS);
    assert_int_equal(data, i + 224);
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
    unit_test(CB_sanity__1),
    unit_test(CB_sanity__2)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
