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

#include "common_ccc.h"
#include "memory.h"

/*---------------------------------------------------------------------------*/

void my_reverse__null(void **state)
  {
  assert_int_equal(my_reverse(NULL, 0), NULL);
  }

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
  {
  const struct CMUnitTest tests[] =
    {
    unit_test(my_reverse__null)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
