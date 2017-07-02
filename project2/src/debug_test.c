/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file debug_test.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 2, 2017
 * @brief This file validates the debug functions.
 */

#include "common_ccc.h"
#include "debug.h"

/*---------------------------------------------------------------------------*/

void component__null(void **state)
  {
  //assert_int_equal(debug(NULL, 0), NULL);
  }

/*---------------------------------------------------------------------------*/

int main(int argc, char *argv[])
  {
  const struct CMUnitTest tests[] =
    {
    unit_test(component__null)
    };
  return cmocka_run_group_tests(tests, NULL, NULL);
  }
