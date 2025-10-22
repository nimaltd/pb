
/*
 * @file        pb.c
 * @brief       Push-Button driver
 * @author      Nima Askari
 * @version     1.0.0
 * @license     See the LICENSE file in the root folder.
 *
 * @note        All my libraries are dual-licensed. 
 *              Please review the licensing terms before using them.
 *              For any inquiries, feel free to contact me.
 *
 * @github      https://www.github.com/nimaltd
 * @linkedin    https://www.linkedin.com/in/nimaltd
 * @youtube     https://www.youtube.com/@nimaltd
 * @instagram   https://instagram.com/github.nimaltd
 *
 * Copyright (C) 2025 Nima Askari - NimaLTD. All rights reserved.
 */

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

#include <string.h>
#include "pb.h"
#include "tim.h"

/*************************************************************************************************/
/** Private Function prototype **/
/*************************************************************************************************/

/* Add a new button event to the queue */
void    pb_evn_add(pb_evn_t event);

/* Periodic timer callback for push-button scan */
void    pb_tim_cb(TIM_HandleTypeDef *htim);

/*************************************************************************************************/
/** Global Variable **/
/*************************************************************************************************/

pb_t    pb_handle;

const   pb_config_t pb_config[] = { PB_CONFIG };

/*************************************************************************************************/
/** Function Implementations **/
/*************************************************************************************************/

/*************************************************************************************************/
/**
 * @brief Initialize the push-button driver.
 * Sets configuration, callback, clears buffers, and starts
 * the timer interrupt for periodic button scanning.
 * @param[in] callback Optional event callback function.
 */
void pb_init(void (*callback)(bool, pb_evn_t))
{
  /* Check that configuration pointer is valid */
  assert_param(config != NULL);

  /* Save configuration and callback */
  pb_handle.callback = callback;

  /* Clear event buffer */
  pb_clear();

  /* Configure timer for PB scanning */
  __HAL_TIM_SET_AUTORELOAD(&PB_TIM, (PB_INTERVAL_MS * 1000) - 1);
  __HAL_TIM_SET_COUNTER(&PB_TIM, 0);

  /* Register callback and start timer interrupt */
  HAL_TIM_RegisterCallback(&PB_TIM, HAL_TIM_PERIOD_ELAPSED_CB_ID, pb_tim_cb);
  HAL_TIM_Base_Start_IT(&PB_TIM);
}

/*************************************************************************************************/
/**
 * @brief Clear pending events.
 */
void pb_clear(void)
{
  /* Reset head and tail indices */
  pb_handle.evn_head = 0;
  pb_handle.evn_tail = 0;

  /* Clear event buffer and press counters */
  memset(pb_handle.evn, 0, sizeof(pb_handle.evn));
  memset(pb_handle.cnt, 0, sizeof(pb_handle.cnt));
}

/*************************************************************************************************/
/**
 * @brief Process pending button events.
 * Retrieves next event from the queue and calls the user callback
 * (if registered). Returns the event for manual polling.
 */
pb_evn_t pb_loop(void)
{
  pb_evn_t event = 0;

  if (pb_handle.evn_head != pb_handle.evn_tail)
  {
    event = pb_handle.evn[pb_handle.evn_tail];
    pb_handle.evn_tail = (pb_handle.evn_tail + 1) % PB_EVN_QUEUE_SIZE;

    if (pb_handle.callback != NULL)
    {
      pb_handle.callback(event & PB_EVN_LONG_MASK, event & (~PB_EVN_LONG_MASK));
    }
  }

  return event;
}

/*************************************************************************************************/
/** Private Implementations **/
/*************************************************************************************************/

/*************************************************************************************************/
/**
 * @brief Add a new button event to the queue.
 * Inserts event at the head index if queue not full.
 * Head is advanced in a circular manner (single-producer safe).
 */
void pb_evn_add(pb_evn_t event)
{
  uint32_t next_head = (pb_handle.evn_head + 1) % PB_EVN_QUEUE_SIZE;

  /* Check if queue is not full */
  if (next_head != pb_handle.evn_tail)
  {
    pb_handle.evn[pb_handle.evn_head] = event;
    pb_handle.evn_head = next_head;
  }
  /* else: queue full */
}

/*************************************************************************************************/
/**
 * @brief Periodic timer callback for push-button scan.
 * Checks each button state (active-low):
 *  - Increments counter while pressed.
 *  - On release, generates short or long press event.
 */
void pb_tim_cb(TIM_HandleTypeDef *htim)
{
  for (uint8_t i = 0; i < PB_CONFIG_COUNT; i++)
  {
    /* Released (logic high) */
    if (pb_config[i].gpio->IDR & pb_config[i].pin)
    {
      if (pb_handle.cnt[i] >= (PB_LONG_TIME_MS / PB_INTERVAL_MS))
      {
        pb_evn_add((1 << i) | PB_EVN_LONG_MASK);
      }
      else if (pb_handle.cnt[i] >= (PB_SHORT_TIME_MS / PB_INTERVAL_MS))
      {
        pb_evn_add(1 << i);
      }

      /* Reset after release */
      pb_handle.cnt[i] = 0;
    }
    /* Pressed (logic low) */
    else
    {
      /* Count press duration */
      pb_handle.cnt[i]++;
    }
  }
}

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/
