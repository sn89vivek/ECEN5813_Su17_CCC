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
    unit_test(CB_destroy__2)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
