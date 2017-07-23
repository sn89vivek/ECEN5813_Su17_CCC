/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/*
 * @file main.c
 * @brief Source file containing main function
 *
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date June 19, 2017
 */

#include "common_ccc.h"

#if defined(PROJECT1)
  #include "project1.h"
#elif defined(PROJECT2)
  #include "project2.h"
#elif defined(PROJECT3)
  #include "project3.h"
#endif

/*---------------------------------------------------------------------------*/

/**
 * @brief Definition of main function
 *
 * @param None
 * @return None
 */
int main()
  {
#if defined(PROJECT1)
  course1();
#elif defined(PROJECT2)
  project2();
#elif defined(PROJECT3)
  project3();
#endif
  return 0;
  }
