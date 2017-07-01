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
 * @file project2.h 
 * @brief This file is to be used to project 2.
 *
 * @author Alex Fosdick
 * @date April 2, 2017
 *
 */
#ifndef __PROJECT2_H__
#define __PROJECT2_H__

#include <stdint.h>

#define BASE_2  (2)
#define BASE_10 (10)
#define BASE_16 (16)

#define DATA_SET_SIZE_W (10)
#define MEM_SET_SIZE_B  (32)
#define MEM_SET_SIZE_W  (8)
#define MEM_ZERO_LENGTH (16)

#define TEST_MEMMOVE_LENGTH (16)
#define TEST_ERROR          (1)
#define TEST_NO_ERROR       (0)
#define TESTCOUNT           (8)

/**
 * @brief function to run project2 materials
 * 
 * This function calls some various simple tests that you can run to test 
 * your code for the project 2. The contents of these functions
 * have been provided. 
 *
 * @return void
 */
void project2(void);

/**
 * @brief function to run project2 data operations
 * 
 * This function calls the my_itoa and my_atoi functions to validate they
 * work as expected for hexadecimal numbers.
 *
 * @return void
 */
int8_t test_data1();

/**
 * @brief function to run project2 data operations
 * 
 * This function calls the my_itoa and my_atoi functions to validate they
 * work as expected for decimal numbers. 
 *
 * @return void
 */
int8_t test_data2();

/**
 * @brief function to test the non-overlapped memmove operation
 * 
 * This function calls the memmove routine with two sets of data that do not
 * over lap in anyway. This function should print that a move worked correctly
 * for a move from source to destination.
 *
 * @return void
 */
int8_t test_memmove1();

/**
 * @brief function to test an overlapped Memmove operation Part 1
 * 
 * This function calls the memmove routine with two sets of data that not
 * over lap. Overlap exists at the start of the destination and the end of the
 * source pointers. This function should print that a move worked correctly
 * for a move from source to destination regardless of overlap.
 *
 * @return void
 */
int8_t test_memmove2();

/**
 * @brief function to run project2 memmove overlapped test
 * 
 * This function calls the memmove routine with two sets of data that not
 * over lap. Overlap exists at the start of the source and the end of the
 * destination pointers. This function should print that a move worked correctly
 * for a move from source to destination regardless of overlap.
 *
 * @return void
 */
int8_t test_memmove3();

/**
 * @brief function to test the memcopy functionality
 * 
 * This function calls the my_memcopy functions to validate a copy works
 * correctly. 
 *
 * @return void
 */
int8_t test_memcpy();

/**
 * @brief function to test the memset and memzero functionality
 * 
 * This function calls the memset and memzero functions. This shoudl zero out
 * the bytes from [] to []. This should set the bytes [] to [] with 0xFF.
 *
 * @return void
 */
int8_t test_memset();

/**
 * @brief function to test the reverse functionality
 * 
 * This function calls the my_reverse function to see if a give set of ASCII
 * characters will properly reverse.
 *
 * @return void
 */
int8_t test_reverse();

/**
 * @brief function to execute all tests
 * 
 * This function calls all of the test functions and displays the results.
 *
 * @return void
 */
void course1(void);

#endif /* __PROJECT2_H__ */
