/*
 * @file main.c
 * @brief source file containing main function
 *
 *
 * @author Robert Blazewicz/Vivek Sankaranarayanan
 * @date June 19, 2017
 */

#include "common_ccc.h"

/**
 * @brief Definition of main function
 * 
 * @param None
 * @return None
 */
int main()
  {
#if defined(PLATFORM_MKL)
  uart_configure();
  while(1) {}
#endif
  return 0;
  }
