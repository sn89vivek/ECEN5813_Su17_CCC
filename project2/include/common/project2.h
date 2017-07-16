/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 2
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project2.h
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 15, 2017
 * @brief Declarations for project2 related functions
 */


#ifndef INCLUDES_PROJECT2_H_
#define INCLUDES_PROJECT2_H_

/*---------------------------------------------------------------------------*/

#define MIN_CB_LENGTH  (0x0004)
#define MAX_CB_LENGTH  (0x100)
#define EOS_CHARACTER  ('\r')

/*---------------------------------------------------------------------------*/

/* Object: proj2_metrics: Metrics for the project2 input sequence */
typedef struct
  {
  uint32_t num_alpha;      /* Number of alphabetic characters */
  uint32_t num_numeric;    /* Number of numeric characters */
  uint32_t num_punct;      /* Number of punctuation characters */
  uint32_t num_misc;       /* Number of miscellaneous characters */
  uint32_t num_total;      /* Number of total characters */
  }proj2_statistics_t;

/* Object: proj2_status: Project2 status enumeration */
typedef enum
  {
  PR_TXBUF_CREATION_FAILED,
  PR_RXBUF_CREATION_FAILED,
  PR_TXBUF_ADD_FAILED,
  PR_TXBUF_REMOVE_FAILED,
  PR_RXBUF_ADD_FAILED,
  PR_RXBUF_REMOVE_FAILED,
  PR_PARSING_IN_PROGRESS,
  PR_PARSING_COMPLETE
  } proj2_status;

/*---------------------------------------------------------------------------*/

/**
 * @brief The function initiates testing of UART and circular buffer functions
 *        for project2
 *
 * @param  none
 * @return This function does not return
 */
void project2();

/*---------------------------------------------------------------------------*/

#endif /* INCLUDES_PROJECT2_H_ */
