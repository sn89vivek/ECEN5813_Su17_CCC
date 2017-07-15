/*
 * @file main.c
 * @brief source file containing main function
 *
 * TODO
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
uint8_t buffer[12];
int main()
  {
#if defined(PLATFORM_MKL)
  uart_configure();
  while(1) {
    uart_receive_n(buffer, 10);
    uart_send_n(buffer, 10);
  }
#endif
  return 0;
  }
