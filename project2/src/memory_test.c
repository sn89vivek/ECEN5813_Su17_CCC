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
/* my_memmove */

void my_memmove__1(void **state)
  {
  uint8_t *dst = (uint8_t*)alloca(1);
  assert_int_equal(my_memmove(NULL, dst, 1), NULL);
  }

void my_memmove__2(void **state)
  {
  uint8_t *src = (uint8_t*)alloca(1);
  assert_int_equal(my_memmove(src, NULL, 1), NULL);
  }

void my_memmove__3(void **state)
  {
  uint8_t *src = (uint8_t*)alloca(1);
  uint8_t *dst = (uint8_t*)alloca(1);
  assert_int_equal(my_memmove(src, dst, 0), NULL);
  }

void my_memmove__4(void **state)
  {
  uint8_t *src = (uint8_t*)alloca(1);
  uint8_t *dst = (uint8_t*)alloca(1);
  assert_int_equal(my_memmove(src, dst, 1), dst);
  }

/*---------------------------------------------------------------------------*/
/* my_memcpy */

/*---------------------------------------------------------------------------*/
/* my_memset */

/*---------------------------------------------------------------------------*/
/* my_memzero */

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
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 1), "a", 1), 0);
  }

void my_reverse__4(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("ab");
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 2), "ba", 2), 0);
  }

void my_reverse__5(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("abc");
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 3), "cba", 3), 0);
  }

void my_reverse__6(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("0123456789");
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 10), "9876543210", 10), 0);
  }

void my_reverse__7(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("0123X6789");
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 9), "9876X3210", 9), 0);
  }

void my_reverse__8(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("0123456789");
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 5), "4321056789", 5), 0);
  }

void my_reverse__9(void **state)
  {
  uint8_t *src = (uint8_t*)strdupa("012345");
  assert_int_equal(strncmp((const char8_t*)my_reverse(src, 6), "5432106789", 6), 0);
  }

void my_reverse__10(void **state)
  {
  uint8_t *src1 = (uint8_t*)alloca(256);
  uint8_t *src2 = (uint8_t*)alloca(256);
  for (size_t i=0; i < 256; i++)
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
