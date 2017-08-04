/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file project1.c
 * @brief This file is to be used to test library functions of project 1.
 *        Original by Alex Fosdick.
 *
 * @author Alex Fosdick
 * @date April 2, 2017
 *
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 19, 2017
 */

#if defined(PROJECT1)

#include <stdio.h>
#include "common_ccc.h"
#include "platform.h"
#include "project1.h"
#include "memory.h"
#include "conversion.h"
#include "debug.h"

#if defined(PLATFORM_HOST) || defined(PLATFORM_BBB)

/*---------------------------------------------------------------------------*/

int8_t test_data1()
  {
  uint8_t * ptr;
  int32_t num = -4096;
  uint32_t digits;
  int32_t value;
  uint8_t status;

  printf("\ntest_data1();\n");
  ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

  if (! ptr )
    {
    return TEST_ERROR;
    }

  digits = my_itoa( num, ptr, BASE_16);
  status = my_atoi( ptr, digits, BASE_16, &value);
  #ifdef VERBOSE
  #if defined(FORMAT_INT32_AS_LONG_INT)
  printf("  Initial number: %ld\n", num);
  printf("  Final Decimal number: %ld\n", value);
  #else
  printf("  Initial number: %d\n", num);
  printf("  Final Decimal number: %d\n", value);
  #endif
  #endif
  free_words( (uint32_t*)ptr );

  if ((status != SUCCESS) || ( value != num ))
    {
    return TEST_ERROR;
    }
  return TEST_NO_ERROR;
  }

/*---------------------------------------------------------------------------*/

int8_t test_data2()
  {
  uint8_t * ptr;
  int32_t num = 123456;
  uint32_t digits;
  int32_t value;
  uint8_t status;

  printf("test_data2();\n");
  ptr = (uint8_t*) reserve_words( DATA_SET_SIZE_W );

  if (! ptr )
    {
    return TEST_ERROR;
    }

  digits = my_itoa( num, ptr, BASE_10);
  status = my_atoi( ptr, digits, BASE_10, &value);
  #ifdef VERBOSE
  #if defined(FORMAT_INT32_AS_LONG_INT)
  printf("  Initial Decimal number: %ld\n", num);
  printf("  Final Decimal number: %ld\n", value);
  #else
  printf("  Initial Decimal number: %d\n", num);
  printf("  Final Decimal number: %d\n", value);
  #endif
  #endif
  free_words( (uint32_t*)ptr );

  if (( status != SUCCESS) || ( value != num ))
    {
    return TEST_ERROR;
    }
  return TEST_NO_ERROR;
  }

/*---------------------------------------------------------------------------*/

int8_t test_memmove1()
  {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("test_memmove1() - NO OVERLAP\n");
  set = (uint8_t*) reserve_words( MEM_SET_SIZE_W );

  if (! set )
    {
    return TEST_ERROR;
    }

  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
    {
    set[i] = i;
    }

  print_memory(set, MEM_SET_SIZE_B);
  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  print_memory(set, MEM_SET_SIZE_B);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    if (set[i + 16] != i)
      {
      ret = TEST_ERROR;
      }
    }

  free_words( (uint32_t*)set );
  return ret;
  }

/*---------------------------------------------------------------------------*/

int8_t test_memmove2()
  {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("test_memmove2() -OVERLAP END OF SRC BEGINNING OF DST\n");
  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

  if (! set )
    {
    return TEST_ERROR;
    }
  ptra = &set[0];
  ptrb = &set[8];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
    {
    set[i] = i;
    }

  print_memory(set, MEM_SET_SIZE_B);
  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  print_memory(set, MEM_SET_SIZE_B);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    if (set[i + 8] != i)
      {
      ret = TEST_ERROR;
      }
    }

  free_words( (uint32_t*)set );
  return ret;
  }

/*---------------------------------------------------------------------------*/

int8_t test_memmove3()
  {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("test_memove3() - OVERLAP END OF DEST BEGINNING OF SRC\n");
  set = (uint8_t*)reserve_words( MEM_SET_SIZE_W);

  if (! set )
    {
    return TEST_ERROR;
    }
  ptra = &set[8];
  ptrb = &set[0];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
    {
    set[i] = i;
    }

  print_memory(set, MEM_SET_SIZE_B);
  my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  print_memory(set, MEM_SET_SIZE_B);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    if (set[i] != (i + 8))
      {
      ret = TEST_ERROR;
      }
    }

  free_words( (uint32_t*)set );
  return ret;
  }

/*---------------------------------------------------------------------------*/

int8_t test_memcpy()
  {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("test_memcpy()\n");
  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);

  if (! set )
    {
    return TEST_ERROR;
    }
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
    {
    set[i] = i;
    }

  print_memory(set, MEM_SET_SIZE_B);
  my_memcpy(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  print_memory(set, MEM_SET_SIZE_B);

  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
    {
    if (set[i+16] != i)
      {
      ret = TEST_ERROR;
      }
    }

  free_words( (uint32_t*)set );
  return ret;
  }

/*---------------------------------------------------------------------------*/

int8_t test_memset()
  {
  uint8_t i;
  uint8_t ret = TEST_NO_ERROR;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  printf("test_memset()\n");
  set = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (! set )
    {
    return TEST_ERROR;
    }
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++)
    {
    set[i] = i;
    }

  print_memory(set, MEM_SET_SIZE_B);
  my_memset(ptra, MEM_SET_SIZE_B, 0xFF);
  print_memory(set, MEM_SET_SIZE_B);
  my_memzero(ptrb, MEM_ZERO_LENGTH);
  print_memory(set, MEM_SET_SIZE_B);

  /* Validate Set & Zero Functionality */
  for (i = 0; i < MEM_ZERO_LENGTH; i++)
    {
    if (set[i] != 0xFF)
      {
      ret = TEST_ERROR;
      }
    if (set[16 + i] != 0)
      {
      ret = TEST_ERROR;
      }
    }

  free_words( (uint32_t*)set );
  return ret;
  }

/*---------------------------------------------------------------------------*/

int8_t test_reverse()
  {
  uint8_t i;
  int8_t ret = TEST_NO_ERROR;
  uint8_t * copy;
  uint8_t set[MEM_SET_SIZE_B] =
    {
    0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26,
    0x48, 0x63, 0x20, 0x66, 0x6F, 0x00, 0x20, 0x33,
    0x72, 0x75, 0x74, 0x78, 0x21, 0x4D, 0x20, 0x40,
    0x20, 0x24, 0x7C, 0x20, 0x24, 0x69, 0x68, 0x54
    };

  printf("test_reverse()\n");
  copy = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (! copy )
    {
    return TEST_ERROR;
    }

  my_memcpy(set, copy, MEM_SET_SIZE_B);

  print_memory(set, MEM_SET_SIZE_B);
  my_reverse(set, MEM_SET_SIZE_B);
  print_memory(set, MEM_SET_SIZE_B);

  for (i = 0; i < MEM_SET_SIZE_B; i++)
    {
    if (set[i] != copy[MEM_SET_SIZE_B - i - 1])
      {
      ret = TEST_ERROR;
      }
    }

  free_words( (uint32_t*)copy );
  return ret;
  }

/*---------------------------------------------------------------------------*/

void project1(void)
  {
  uint8_t i;
  int8_t failed = 0;
  int8_t results[TESTCOUNT] = {0,0,0,0,0,0,0,0};

  results[0] = test_data1();
  results[1] = test_data2();
  results[2] = test_memmove1();
  results[3] = test_memmove2();
  results[4] = test_memmove3();
  results[5] = test_memcpy();
  results[6] = test_memset();
  results[7] = test_reverse();

  for ( i = 0; i < TESTCOUNT; i++)
    {
    #ifdef VERBOSE
    if (results[i] != 0)
      {
      printf("Test %d failed\n", i);
      }
    #endif
    failed += results[i];
    }

  printf("--------------------------------\n");
  printf("Test Results:\n");
  printf("  PASSED: %d / %d\n", (TESTCOUNT - failed), TESTCOUNT);
  printf("  FAILED: %d / %d\n", failed, TESTCOUNT);
  printf("--------------------------------\n");
  }

/*---------------------------------------------------------------------------*/

#elif defined(PLATFORM_MKL)

void project1()
  {
  }

/*---------------------------------------------------------------------------*/

#endif /* PLATFORM_MKL */

#endif /* PROJECT1 */
