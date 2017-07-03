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

/* Add strdupa() */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
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
/* my_memmove */

void my_memmove__1(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memmove(NULL, data, 1), NULL);
  }

void my_memmove__2(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memmove(data, NULL, 1), NULL);
  }

void my_memmove__3(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memmove(data, data, 0), NULL);
  }

void my_memmove__4(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memmove(data, data, 1), data);
  }

/* Test no-overlap condition */
void my_memmove__5(void **state)
  {
  uint8_t *data;
  uint8_t *ptra;
  uint8_t *ptrb;

  data = (uint8_t*)alloca(MEM_SET_SIZE_W);
  assert_non_null(data);
  ptra = &data[0];
  ptrb = &data[16];

  // Initialize the set to test values
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++)
    {
    data[i] = i;
    }

  assert_int_equal(my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i + 16], i);
    }
  }

/* Test source in destination region overlap */
void my_memmove__6(void **state)
  {
  uint8_t *data;
  uint8_t *ptra;
  uint8_t *ptrb;

  data = (uint8_t*)alloca(MEM_SET_SIZE_W);
  assert_non_null(data);
  ptra = &data[0];
  ptrb = &data[8];

  // Initialize the set to test values
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++)
    {
    data[i] = i;
    }

  assert_int_equal(my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i + 8], i);
    }
  }

/* Test destination in source region overlap */
void my_memmove__7(void **state)
  {
  uint8_t *data;
  uint8_t *ptra;
  uint8_t *ptrb;

  data = (uint8_t*)alloca(MEM_SET_SIZE_W);
  assert_non_null(data);
  ptra = &data[8];
  ptrb = &data[0];

  // Initialize the set to test values
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++)
    {
    data[i] = i;
    }

  assert_int_equal(my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i], i + 8);
    }
  }

/*---------------------------------------------------------------------------*/
/* my_memcpy */

void my_memcpy__1(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memcpy(NULL, data, 1), NULL);
  }

void my_memcpy__2(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memcpy(data, NULL, 1), NULL);
  }

void my_memcpy__3(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memcpy(data, data, 0), NULL);
  }

void my_memcpy__4(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memcpy(data, data, 1), data);
  }

void my_memcpy__5(void **state)
  {
  uint8_t *data;
  uint8_t *ptra;
  uint8_t *ptrb;

  data = (uint8_t*)alloca(MEM_SET_SIZE_W);
  assert_non_null(data);
  ptra = &data[0];
  ptrb = &data[16];

  // Initialize the set to test values
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++)
    {
    data[i] = i;
    }

  assert_int_equal(my_memcpy(ptra, ptrb, TEST_MEMMOVE_LENGTH), ptrb);

  for (size_t i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    assert_int_equal(data[i+16], i);
    }
  }

/*---------------------------------------------------------------------------*/
/* my_memset */

void my_memset__1(void **state)
  {
  assert_int_equal(my_memset(NULL, 1, 0), NULL);
  }

void my_memset__2(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memset(data, 0, 0), NULL);
  }

void my_memset__3(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memset(data, 1, 0), data);
  }

void my_memset__4(void **state)
  {
  uint8_t *data;
  uint8_t *ptra;
  uint8_t *ptrb;

  data = (uint8_t*)alloca(MEM_SET_SIZE_W);
  assert_non_null(data);
  ptra = &data[0];
  ptrb = &data[16];

  // Initialize the set to test values
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++) 
    {
    data[i] = i;
    }

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
/* my_memzero */

void my_memzero__1(void **state)
  {
  assert_int_equal(my_memzero(NULL, 1), NULL);
  }

void my_memzero__2(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memzero(data, 0), NULL);
  }

void my_memzero__3(void **state)
  {
  uint8_t *data = (uint8_t*)alloca(1);
  assert_non_null(data);
  assert_int_equal(my_memzero(data, 1), data);
  }

void my_memzero__4(void **state)
  {
  uint8_t *data;
  uint8_t *ptr;

  data = (uint8_t*)alloca(MEM_SET_SIZE_W);
  assert_non_null(data);
  ptr = &data[0];

  // Initialize the set to test values
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++) 
    {
    data[i] = i;
    }

  assert_int_equal(my_memzero(ptr, MEM_SET_SIZE_B), ptr);

  // Validate zero functionality
  for (size_t i = 0; i < MEM_SET_SIZE_B; i++)
    {
    assert_int_equal(data[i], 0);
    }
  }

/*---------------------------------------------------------------------------*/
/* my_reverse */

void my_reverse__1(void **state)
  {
  assert_int_equal(my_reverse(NULL, 0), NULL);
  }

void my_reverse__2(void **state)
  {
  assert_int_equal(my_reverse((uint8_t*)"abc", 0), NULL);
  }

void my_reverse__3(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("a");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 1), "a", 1), 0);
  }

void my_reverse__4(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("ab");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 2), "ba", 2), 0);
  }

void my_reverse__5(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("abc");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 3), "cba", 3), 0);
  }

void my_reverse__6(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("0123456789");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 10), "9876543210", 10), 0);
  }

void my_reverse__7(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("0123X6789");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 9), "9876X3210", 9), 0);
  }

void my_reverse__8(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("0123456789");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 5), "4321056789", 5), 0);
  }

void my_reverse__9(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("012345");
  assert_non_null(src);
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 6), "5432106789", 6), 0);
  }

void my_reverse__10(void **state)
  {
  uint8_t *src1 = (uint8_t*)alloca(256);
  uint8_t *src2 = (uint8_t*)alloca(256);
  assert_non_null(src1);
  assert_non_null(src2);

  for (size_t i = 0; i < 256; i++)
    {
    src1[i] = i;
    src2[i] = 255 - i;
    }

  assert_int_equal(strncmp((const char8_t*)my_reverse(src1, 256), (const char8_t*)src2, 256), 0);
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
