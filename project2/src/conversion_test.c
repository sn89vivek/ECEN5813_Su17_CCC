/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file conversion_test.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 2, 2017
 * @brief This file validates the conversion functions.
 */

/* Add strdupa() */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>

#include "common_ccc.h"
#include "conversion.h"

/*---------------------------------------------------------------------------*/

#define BUFFER_SIZE  (1+32+1)

/*---------------------------------------------------------------------------*/

void my_itoa__1(void **state)
  {
  assert_int_equal(my_itoa(0, NULL, 2), 0);
  }

void my_itoa__2(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(0, buffer, 1), 0);
  }

void my_itoa__3(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(0, buffer, 17), 0);
  }

void my_itoa__4(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(-4096, buffer, 16), 5);
  assert_int_equal(strcmp((const char8_t*)buffer, "-1000"), 0);
  }

void my_itoa__5(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(123456, buffer, 10), 6);
  assert_int_equal(strcmp((const char8_t*)buffer, "123456"), 0);
  }

/*---------------------------------------------------------------------------*/

void my_atoi__1(void **state)
  {
  int32_t data;
  assert_int_equal(my_atoi(NULL, 1, 2, &data), FAILURE);
  }

void my_atoi__2(void **state)
  {
  int32_t data;
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 0, 2, &data), FAILURE);
  }

void my_atoi__3(void **state)
  {
  int32_t data;
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 1, &data), FAILURE);
  }

void my_atoi__4(void **state)
  {
  int32_t data;
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 17, &data), FAILURE);
  }

void my_atoi__5(void **state)
  {
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 2, NULL), FAILURE);
  }

void my_atoi__6(void **state)
  {
  int32_t data;
  char8_t buffer[] = "-1000";
  assert_int_equal(my_atoi((uint8_t*)buffer, 5, 16, &data), SUCCESS);
  assert_int_equal(data, -4096);
  }

void my_atoi__7(void **state)
  {
  int32_t data;
  char8_t buffer[] = "123456";
  assert_int_equal(my_atoi((uint8_t*)buffer, 6, 10, &data), SUCCESS);
  assert_int_equal(data, 123456);
  }

/*---------------------------------------------------------------------------*/

void big_to_little32__1(void **state)
  {
  assert_int_equal(big_to_little32(NULL, 1), FAILURE);
  }

void big_to_little32__2(void **state)
  {
  uint32_t data;
  assert_int_equal(big_to_little32(&data, 0), FAILURE);
  }

void big_to_little32__3(void **state)
  {
  uint32_t data = 0x5D29CF37;
  assert_int_equal(big_to_little32(&data, 1), SUCCESS);
  assert_int_equal(data, 0x37CF295D);
  }

void big_to_little32__4(void **state)
  {
  uint32_t data[4] =
    {
    0x12FE34DC,
    0x5D29CF37,
    0xDEADBEEF,
    0x87654321
    };
  assert_int_equal(big_to_little32(data, 3), SUCCESS);
  assert_int_equal(data[0], 0xDC34FE12);
  assert_int_equal(data[1], 0x37CF295D);
  assert_int_equal(data[2], 0xEFBEADDE);
  assert_int_equal(data[3], 0x87654321);
  }

/*---------------------------------------------------------------------------*/

void little_to_big32__1(void **state)
  {
  assert_int_equal(little_to_big32(NULL, 1), FAILURE);
  }

void little_to_big32__2(void **state)
  {
  uint32_t data;
  assert_int_equal(little_to_big32(&data, 0), FAILURE);
  }

void little_to_big32__3(void **state)
  {
  uint32_t data = 0x5D29CF37;
  assert_int_equal(little_to_big32(&data, 1), SUCCESS);
  assert_int_equal(data, 0x37CF295D);
  }

void little_to_big32__4(void **state)
  {
  uint32_t data[4] =
    {
    0x12FE34DC,
    0x5D29CF37,
    0xDEADBEEF,
    0x87654321
    };
  assert_int_equal(little_to_big32(data, 3), SUCCESS);
  assert_int_equal(data[0], 0xDC34FE12);
  assert_int_equal(data[1], 0x37CF295D);
  assert_int_equal(data[2], 0xEFBEADDE);
  assert_int_equal(data[3], 0x87654321);
  }

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
  {
  const struct CMUnitTest tests[] =
    {
    unit_test(my_itoa__1),
    unit_test(my_itoa__2),
    unit_test(my_itoa__3),
    unit_test(my_itoa__4),
    unit_test(my_itoa__5),
    unit_test(my_atoi__1),
    unit_test(my_atoi__2),
    unit_test(my_atoi__3),
    unit_test(my_atoi__4),
    unit_test(my_atoi__5),
    unit_test(my_atoi__6),
    unit_test(my_atoi__7),
    unit_test(big_to_little32__1),
    unit_test(big_to_little32__2),
    unit_test(big_to_little32__3),
    unit_test(big_to_little32__4),
    unit_test(little_to_big32__1),
    unit_test(little_to_big32__2),
    unit_test(little_to_big32__3),
    unit_test(little_to_big32__4)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
