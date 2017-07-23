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

/**
 * @brief For function my_itoa(), validate arg 'ptr' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_itoa__1(void **state)
  {
  assert_int_equal(my_itoa(0, NULL, 2), 0);
  }

/**
 * @brief For function my_itoa(), validate arg 'base' with invalid low value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_itoa__2(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(0, buffer, 1), 0);
  }

/**
 * @brief For function my_itoa(), validate arg 'base' with invalid high value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_itoa__3(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(0, buffer, 17), 0);
  }

/**
 * @brief For function my_itoa(), validate value zero in each base from 2-16.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_itoa__4(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  for (uint8_t i = 2; i <= 16; i++)
    {
    assert_int_equal(my_itoa(0, buffer, i), 1);
    assert_string_equal((const char8_t*)buffer, "0");
    }
  }

/**
 * @brief For function my_itoa(), validate a base 10 conversion.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_itoa__5(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(-4096, buffer, 16), 5);
  assert_string_equal((const char8_t*)buffer, "-1000");
  }

/**
 * @brief For function my_itoa(), validate base 16 conversion.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_itoa__6(void **state)
  {
  uint8_t *buffer = (uint8_t*)alloca(BUFFER_SIZE);
  assert_non_null(buffer);
  assert_int_equal(my_itoa(123456, buffer, 10), 6);
  assert_string_equal((const char8_t*)buffer, "123456");
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function my_atoi(), validate arg 'ptr' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__1(void **state)
  {
  int32_t data;
  assert_int_equal(my_atoi(NULL, 1, 2, &data), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate arg 'digits' with invalid value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__2(void **state)
  {
  int32_t data;
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 0, 2, &data), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate arg 'digits' with invalid low value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__3(void **state)
  {
  int32_t data;
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 1, &data), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate arg 'digits' with invalid high
 *        value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__4(void **state)
  {
  int32_t data;
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 17, &data), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate arg 'data' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__5(void **state)
  {
  char8_t buffer[] = "";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 2, NULL), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate failure of negative sign with no
 *        digits.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__6(void **state)
  {
  int32_t data;
  char8_t buffer[] = "-";
  assert_int_equal(my_atoi((uint8_t*)buffer, 1, 10, &data), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate failure when non-numeric values of
 *        selected base are in the input string.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__7(void **state)
  {
  char8_t buffer[] = "123x";
  int32_t data;
  assert_int_equal(my_atoi((uint8_t*)buffer, 4, 16, &data), FAILURE);
  }

/**
 * @brief For function my_atoi(), validate base 16 conversion.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__8(void **state)
  {
  int32_t data;
  char8_t buffer[] = "-1000";
  assert_int_equal(my_atoi((uint8_t*)buffer, 5, 16, &data), SUCCESS);
  assert_int_equal(data, -4096);
  }

/**
 * @brief For function my_atoi(), validate base 10 conversion.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_atoi__9(void **state)
  {
  int32_t data;
  char8_t buffer[] = "123456";
  assert_int_equal(my_atoi((uint8_t*)buffer, 6, 10, &data), SUCCESS);
  assert_int_equal(data, 123456);
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function big_to_little32(), validate arg 'data' with invalid
 *        value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void big_to_little32__1(void **state)
  {
  assert_int_equal(big_to_little32(NULL, 1), FAILURE);
  }

/**
 * @brief For function big_to_little32(), validate arg 'length' with invalid
 *        size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void big_to_little32__2(void **state)
  {
  uint32_t data;
  assert_int_equal(big_to_little32(&data, 0), FAILURE);
  }

/**
 * @brief For function big_to_little32(), validate conversion of 1 value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void big_to_little32__3(void **state)
  {
  uint32_t data = 0x5D29CF37;
  assert_int_equal(big_to_little32(&data, 1), SUCCESS);
  assert_int_equal(data, 0x37CF295D);
  }

/**
 * @brief For function big_to_little32(), validate conversion of multiple
 *        values.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
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

/**
 * @brief For function little_to_big32(), validate arg 'data' with invalid
 *        value NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void little_to_big32__1(void **state)
  {
  assert_int_equal(little_to_big32(NULL, 1), FAILURE);
  }

/**
 * @brief For function little_to_big32(), validate arg 'length' with invalid
 *        size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void little_to_big32__2(void **state)
  {
  uint32_t data;
  assert_int_equal(little_to_big32(&data, 0), FAILURE);
  }

/**
 * @brief For function little_to_big32(), validate conversion of 1 value.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void little_to_big32__3(void **state)
  {
  uint32_t data = 0x5D29CF37;
  assert_int_equal(little_to_big32(&data, 1), SUCCESS);
  assert_int_equal(data, 0x37CF295D);
  }

/**
 * @brief For function little_to_big32(), validate conversion of multiple
 *        values.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
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
    unit_test(my_itoa__6),
    unit_test(my_atoi__1),
    unit_test(my_atoi__2),
    unit_test(my_atoi__3),
    unit_test(my_atoi__4),
    unit_test(my_atoi__5),
    unit_test(my_atoi__6),
    unit_test(my_atoi__7),
    unit_test(my_atoi__8),
    unit_test(my_atoi__9),
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
