
/*
 * @file        pb.h
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

#ifndef _PB_H_
#define _PB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

#include <stdbool.h>
#include "main.h"
#include "pb_config.h"

/*************************************************************************************************/
/** Definitions **/
/*************************************************************************************************/

/* Mask to indicate a long press event in pb_evn_t */
#define PB_EVN_LONG_MASK      0x80000000

/*************************************************************************************************/
/** Typedef/Struct/Enum **/
/*************************************************************************************************/

/*************************************************************************************************/
/* Button event type (bitmask + optional long press flag) */
typedef uint32_t      pb_evn_t;

/*************************************************************************************************/
/* Configuration structure for a single push-button */
typedef struct __PACKED
{
  GPIO_TypeDef        *gpio;
  uint16_t            pin;

} pb_config_t;

/*************************************************************************************************/
/* Main handle for push-button driver */
typedef struct
{
  pb_config_t         *config;                    /* Pointer to button configuration array */
  void                (*callback)(bool, pb_evn_t);/* Optional event callback: is_long, key_mask */
  uint16_t            cnt[PB_KEY_COUNT];          /* Press duration counters for each button */
  pb_evn_t            evn[PB_EVN_QUEUE_SIZE];     /* Circular event buffer */
  __IO uint32_t       evn_head;                   /* Head index of the event queue (written by ISR) */
  __IO uint32_t       evn_tail;                   /* Tail index of the event queue (read by main loop) */

} pb_t;

/*************************************************************************************************/
/** API Functions **/
/*************************************************************************************************/

/* Initialize the push-button driver */
void      pb_init(const pb_config_t *config, void (*callback)(bool, pb_evn_t));

/* Process pending button events */
pb_evn_t  pb_loop(void);

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* _PB_H_ */
