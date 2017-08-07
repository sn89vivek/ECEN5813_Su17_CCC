/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 3
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project3.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 22, 2017
 * @brief Declarations for project2 related functions
 */

#ifndef __PROJECT3_H__
#define __PROJECT3_H__

/*---------------------------------------------------------------------------*/

/** Object: rx_metrics_t: Rx metrics from UART */
typedef struct
  {
  uint32_t alpha;      /* Number of alphabetic characters */
  uint32_t numeric;    /* Number of numeric characters */
  uint32_t punct;      /* Number of punctuation characters */
  uint32_t misc;       /* Number of miscellaneous characters */
  uint32_t total;      /* Number of total characters */
  } metrics_t;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function initiates... for project3
 *
 * @param  none
 * @return This function does not return
 */
void project3();

/*---------------------------------------------------------------------------*/

#endif /* __PROJECT3_H__ */
