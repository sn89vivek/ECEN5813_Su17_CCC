/*-----------------------------------------------------------------------------
 * ECEN-5813 Summer 2017
 * Project 1
 *
 * Copyright (C) 2017 by Robert Blazewicz and Vivek Sankaranarayanan.
 * All Rights Reserved. (This work is unpublished)
 *---------------------------------------------------------------------------*/
/**
 * @file project2.c
 * @author Robert Blazewicz
 * @author Vivek Sankaranarayanan
 * @date July 15, 2017
 * @brief This file contains definition of project2 related tasks
 */

#include "common_ccc.h"
#include "circbuf.h"
#include "project2.h"

/*---------------------------------------------------------------------------*/
/* Declarations                                                              */

void proj2_err(proj2_status pr_stat, CB_status cb_stat);

/*---------------------------------------------------------------------------*/

void project2()
  {
  CB_status status;

  /* Create Tx buffers */
  CB_init(&CB_tx, 8);
  if(status != CB_SUCCESS)
    proj2_err(PR_TXBUF_CREATION_FAILED, status);

  /* Create Rx buffer */
  CB_init(&CB_rx, 8);
  if(status != CB_SUCCESS)
    proj2_err(PR_RXBUF_CREATION_FAILED, status);

  while(1) {}
  }

/*---------------------------------------------------------------------------*/

/*
 * @brief This function handles the errors generated in project2
 *
 * This function handles errors for project2. Uart interrupts are disabled and
 * error is printed out to terminal using blocking uart transmit functions.
 * After printing error, any cleanup if required needs to be performed and
 * then the function blocks forever.
 *
 * @param pr_stat: Project related status flag
 * @param cb_stat: Circular buffer related status flag
 */
void proj2_err(proj2_status pr_stat, CB_status cb_stat)
  {
  // TODO
  while(1) {}
  }
