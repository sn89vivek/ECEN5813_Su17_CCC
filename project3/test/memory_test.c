/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file memory_test.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 1, 2017
 * @brief This file validates the memory functions.
 */

#include <string.h>

#include "common_ccc.h"
#include "memory.h"

/*---------------------------------------------------------------------------*/

#define DATA_SET_SIZE_W      (10)
#define MEM_SET_SIZE_B       (32)
#define MEM_SET_SIZE_W       (8)
#define MEM_ZERO_LENGTH      (16)
#define TEST_MEMMOVE_LENGTH  (16)

/*---------------------------------------------------------------------------*/

/**
 * @brief For function my_memmove(), validate arg 'src' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__1(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memmove(NULL, data, 1), NULL);
  }

/**
 * @brief For function my_memmove(), validate arg 'dst' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__2(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memmove(data, NULL, 1), NULL);
  }

/**
 * @brief For function my_memmove(), validate arg 'length' with invalid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__3(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memmove(data, data, 0), NULL);
  }

/**
 * @brief For function my_memmove(), validate arg 'length' with valid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__4(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memmove(data, data, 1), data);
  }

/**
 * @brief For function my_memmove(), validate memory move with no-overlap
 *        condition.The approach is based on an open-coded test provided by
 *        Alex Fosdick in project 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__5(void **state)
  {
  uint8_t data[MEM_SET_SIZE_B] =
    {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
  uint8_t *ptra = data;
  uint8_t *ptrb = &data[16];

  assert_int_equal(my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i + 16], i);
    }
  }

/**
 * @brief For function my_memmove(), validate memory move with source in
 *        destination region overlap condition. The approach is based on an
 *        open-coded test provided by Alex Fosdick in project 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__6(void **state)
  {
  uint8_t data[MEM_SET_SIZE_B] =
    {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
  uint8_t *ptra = data;
  uint8_t *ptrb = &data[8];

  assert_int_equal(my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i + 8], i);
    }
  }

/**
 * @brief For function my_memmove(), validate memory move with destination in
 *        source region overlap condition. The approach is based on an
 *        open-coded test provided by Alex Fosdick in project 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memmove__7(void **state)
  {
  uint8_t data[MEM_SET_SIZE_B] =
    {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
  uint8_t *ptra = &data[8];
  uint8_t *ptrb = data;

  assert_int_equal(my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i], i + 8);
    }
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function my_memcpy(), validate arg 'src' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memcpy__1(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memcpy(NULL, data, 1), NULL);
  }

/**
 * @brief For function my_memcpy(), validate arg 'dst' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memcpy__2(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memcpy(data, NULL, 1), NULL);
  }

/**
 * @brief For function my_memcpy(), validate arg 'length' with invalid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memcpy__3(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memcpy(data, data, 0), NULL);
  }

/**
 * @brief For function my_memcpy(), validate arg 'length' with valid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memcpy__4(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memcpy(data, data, 1), data);
  }

/**
 * @brief For function my_memcpu(), validate memory copy. The approach is
 *        based on an open-coded test provided by Alex Fosdick in project 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memcpy__5(void **state)
  {
  uint8_t data[MEM_SET_SIZE_B] =
    {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
  uint8_t *ptra = data;
  uint8_t *ptrb = &data[16];

  assert_int_equal(my_memcpy(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i+16], i);
    }
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function my_memset(), validate arg 'src' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memset__1(void **state)
  {
  assert_int_equal(my_memset(NULL, 1, 0), NULL);
  }

/**
 * @brief For function my_memset(), validate arg 'length' with invalid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memset__2(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memset(data, 0, 0), NULL);
  }

/**
 * @brief For function my_memset(), validate setting a single target byte.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memset__3(void **state)
  {
  uint8_t data[1] = { 0xFF };
  assert_int_equal(my_memset(data, 1, 0xDD), data);
  assert_int_equal(data[0], 0xDD);
  }

/**
 * @brief For function my_memset(), validate set and zeroing functionallity.
 *        The approach is based on an open-coded test provided by Alex Fosdick
 *        in project 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memset__4(void **state)
  {
  uint8_t data[MEM_SET_SIZE_B] =
    {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
  uint8_t *ptra = data;
  uint8_t *ptrb = &data[16];

  assert_int_equal(my_memset(ptra, MEM_SET_SIZE_B, 0xFF), ptra);

  assert_int_equal(my_memzero(ptrb, MEM_ZERO_LENGTH), ptrb);

  // Validate set & zero functionality
  for (size_t i = 0; i < MEM_ZERO_LENGTH; i++)
    {
    assert_int_equal(data[i], 0xFF);
    assert_int_equal(data[16 + i], 0);
    }
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function my_memzero(), validate arg 'src' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memzero__1(void **state)
  {
  assert_int_equal(my_memzero(NULL, 1), NULL);
  }

/**
 * @brief For function my_memzero(), validate arg 'length' with invalid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memzero__2(void **state)
  {
  uint8_t data[1];
  assert_int_equal(my_memzero(data, 0), NULL);
  }

/**
 * @brief For function my_memzero(), validate zeroing a single target byte.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memzero__3(void **state)
  {
  uint8_t data[1] = { 0xFF };
  assert_int_equal(my_memzero(data, 1), data);
  assert_int_equal(data[0], 0x00);
  }

/**
 * @brief For function my_memzero(), validate memory zeroing. The approach is
 *        based on an open-coded test provided by Alex Fosdick in project 1.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_memzero__4(void **state)
  {
  uint8_t data[MEM_SET_SIZE_B] =
    {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    };
  uint8_t *ptr = data;

  assert_int_equal(my_memzero(ptr, MEM_SET_SIZE_B), ptr);

  // Validate zero functionality
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++)
    {
    assert_int_equal(data[i], 0);
    }
  }

/*---------------------------------------------------------------------------*/

/**
 * @brief For function my_reverse(), validate arg 'src' with invalid value
 *        NULL.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__1(void **state)
  {
  assert_int_equal(my_reverse(NULL, 0), NULL);
  }

/**
 * @brief For function my_reverse(), validate arg 'length' with invalid size.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__2(void **state)
  {
  assert_int_equal(my_reverse((uint8_t*)"abc", 0), NULL);
  }

/**
 * @brief For function my_reverse(), validate a string of 1 char.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__3(void **state)
  {
  uint8_t src[] = "a";
  assert_string_equal((const char8_t*)my_reverse(src, 1), "a");
  }

/**
 * @brief For function my_reverse(), validate a string of 2 chars.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__4(void **state)
  {
  uint8_t src[] = "ab";
  assert_string_equal((const char8_t*)my_reverse(src, 2), "ba");
  }

/**
 * @brief For function my_reverse(), validate a string of 3 chars.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__5(void **state)
  {
  uint8_t src[] = "abc";
  assert_string_equal((const char8_t*)my_reverse(src, 3), "cba");
  }

/**
 * @brief For function my_reverse(), validate a string of 10 chars.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__6(void **state)
  {
  uint8_t src[] = "0123456789";
  assert_string_equal((const char8_t*)my_reverse(src, 10), "9876543210");
  }

/**
 * @brief For function my_reverse(), validate a string of 9 chars.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__7(void **state)
  {
  uint8_t src[] = "0123X6789";
  assert_string_equal((const char8_t*)my_reverse(src, 9), "9876X3210");
  }

/**
 * @brief For function my_reverse(), validate a string of 10 chars and a
 *        smaller length of only 5.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__8(void **state)
  {
  uint8_t src[] = "0123456789";
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 5), "4321056789", 5), 0);
  }

/**
 * @brief For function my_reverse(), validate a string of 6 chars and a larger
 *        length of 6 against a longer string.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__9(void **state)
  {
  uint8_t src[] = "012345";
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 6), "5432106789", 6), 0);
  }

/**
 * @brief For function my_reverse(), validate reveral of a raw buffer with
 *        values from 0 to 255.
 *
 * @param  state - Cmocka state handle
 *
 * @return Nothing
 */
void my_reverse__10(void **state)
  {
  uint8_t src1[256];
  uint8_t src2[256];

  for (size_t i = 0; i < 256; i++)
    {
    src1[i] = i;
    src2[i] = 255 - i;
    }

  assert_int_equal(my_reverse(src1, 256), src1);
  for (size_t i = 0; i < 256; i++)
    {
    assert_int_equal(src1[i], src2[i]);
    }
  }

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
  {
  const struct CMUnitTest tests[] =
    {
    unit_test(my_memmove__1),
    unit_test(my_memmove__2),
    unit_test(my_memmove__3),
    unit_test(my_memmove__4),
    unit_test(my_memmove__5),
    unit_test(my_memmove__6),
    unit_test(my_memmove__7),
    unit_test(my_memcpy__1),
    unit_test(my_memcpy__2),
    unit_test(my_memcpy__3),
    unit_test(my_memcpy__4),
    unit_test(my_memcpy__5),
    unit_test(my_memset__1),
    unit_test(my_memset__2),
    unit_test(my_memset__3),
    unit_test(my_memset__4),
    unit_test(my_memzero__1),
    unit_test(my_memzero__2),
    unit_test(my_memzero__3),
    unit_test(my_memzero__4),
    unit_test(my_reverse__1),
    unit_test(my_reverse__2),
    unit_test(my_reverse__3),
    unit_test(my_reverse__4),
    unit_test(my_reverse__5),
    unit_test(my_reverse__6),
    unit_test(my_reverse__7),
    unit_test(my_reverse__8),
    unit_test(my_reverse__9),
    unit_test(my_reverse__10)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
