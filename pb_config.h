
/*
 * @file        pb_config.h
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

#ifndef _PB_CONFIG_H_
#define _PB_CONFIG_H_

/*************************************************************************************************/
/** Includes **/
/*************************************************************************************************/

/* USER CODE BEGIN PB_INCLUDES */

/* USER CODE END PB_INCLUDES */

/*************************************************************************************************/
/** Configurations **/
/*************************************************************************************************/

/* USER CODE BEGIN PB_CONFIGURATION */

/* Timer used for periodic button scanning */
#define PB_TIM              htim3

/* Timer interval in milliseconds (scan period) */
#define PB_INTERVAL_MS      10

/* Minimum press duration (ms) to register a short press */
#define PB_SHORT_TIME_MS    50

/* Minimum press duration (ms) to register a long press */
#define PB_LONG_TIME_MS     1000

/* Size of the event queue (number of events that can be stored) */
#define PB_EVN_QUEUE_SIZE   4

/* Number of buttons configured */
#define PB_CONFIG_COUNT     3

/* Pin definitions */
#define PB_CONFIG           {.gpio = KEY_DOWN_GPIO_Port,  .pin = KEY_DOWN_Pin}, \
                            {.gpio = KEY_UP_GPIO_Port,    .pin = KEY_UP_Pin},   \
                            {.gpio = KEY_ENTER_GPIO_Port, .pin = KEY_ENTER_Pin}

/* USER CODE END PB_CONFIGURATION */

/*************************************************************************************************/
/** End of File **/
/*************************************************************************************************/

#endif /* _PB_CONFIG_H_ */
