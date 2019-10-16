/** @file    keypad.h
  * @version 0.1
  * @author  minhneo
  * @brief   
  *          + Initialization and de-initialization functions
  *             ++ 
  *          + Operation functions
  *             ++
  *          + Control functions
  *             ++
  *          + State functions
  *             ++
  */

#ifndef __KEYPAD_H__
#define __KEYPAD_H__
/*********************************************************************************
 * INCLUDE
 */
 
/* C Library */
#include "stdint.h"
/* Sys Library */
/* User Library */

/*********************************************************************************
* DEFINE
*/
#define KEY_EVENT_NUM                                       2
/***********************************************************************
* TYPEDEF
*/

/**
 * @brief Keypad action group event 
 **/
typedef enum
{
  KEY_PRESS,
  KEY_HOLD,
}key_event_t;

/**
  * @brief  Keypad Status enumeration
  */
typedef enum
{
  KEYPAD_OK,
  KEYPAD_ERROR,
}keypadStatus_t;

/**
  * @brief  Key definition
  */
typedef enum
{
  KEY_NONE = 0x00,
  KEY_UP,
  KEY_DOWN,
  KEY_OK,
  KEY_EXIT,
}keypress_t;

typedef void (*key_callback_t) (key_event_t event, uint8_t Keycode);
/*********************************************************************************
* STATIC VARIABLE
*/

/**
 * @brief Set register value callback function
 **/


/*********************************************************************************
 * EXPORT FUNCTION
 */

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
keypadStatus_t Keypad_Init(void);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Keypad_InstallCallback(key_event_t event, key_callback_t fcallback);
 /**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */

void Keypad_Process(void);
#endif /* __KEYPAD_H__ */
