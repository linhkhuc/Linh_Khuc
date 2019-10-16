/** @file    keypad.c
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

/*********************************************************************************
 * INCLUDE
 */
 
/* C Library */
/* Sys Library */
#include "gpio.h"
/* User Library */
#include "keypad.h"

/*********************************************************************************
* DEFINE
*/

#define NUM_BUTTON                                          4

#define KEY_HOLD_TIME_START                                 1000
#define KEY_HOLE_TIME_PERIOD                                150
/***********************************************************************
* TYPEDEF
*/

/*********************************************************************************
* STATIC VARIABLE
*/

/**
 * @brief Led 7 segment data port
 **/
static GPIO_TypeDef* GPIO_PORT[NUM_BUTTON] = {GPIOB};
  
/**
 * @brief Led 7 segment data pin
 **/
/*********************************************************************/
/* |   GPIO_PIN_3  |   GPIO_PIN_4  |   GPIO_PIN_5   |   GPIO_PIN_6   */
/* |      UP       |      DOWN     |       OK       |      EXIT      */
static const uint16_t GPIO_PIN[NUM_BUTTON] = {GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6};

static key_callback_t g_callback[KEY_EVENT_NUM] = {NULL};
static uint32_t keypad_tick = 0;
static uint8_t keypress = 0;


/*********************************************************************************
 * STATIC FUNCTION
 */
static uint8_t ScanKey(void);
static uint32_t keypad_GetTick(void);
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
keypadStatus_t Keypad_Init(void)
{
  keypress = KEY_NONE;
  return KEYPAD_OK;
}

/**
 * @brief  
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Keypad_InstallCallback(key_event_t event, key_callback_t fcallback)
{
  g_callback[event] = fcallback;
}

 /**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */

void Keypad_Process(void)
{
  uint8_t key = ScanKey();
  if(key != KEY_NONE) /*< Neu co phim duoc nhan >*/
  {
    if(keypress == KEY_NONE) /*< Xac dinh nhan phim >*/
    {
      keypress = key;
      if(g_callback[KEY_PRESS] != NULL) g_callback[KEY_PRESS](KEY_PRESS, keypress);
      keypad_tick = keypad_GetTick();
    }
    else /*< Xac dinh giu phim >*/
    {
      if(keypad_GetTick() - keypad_tick > KEY_HOLD_TIME_START)
      {
        keypad_tick = keypad_GetTick() - KEY_HOLD_TIME_START + KEY_HOLE_TIME_PERIOD;
        if(g_callback[KEY_HOLD] != NULL) g_callback[KEY_HOLD](KEY_HOLD, keypress);
      }
    }
  }
  else   /*< Neu khong co phim nao duoc nhan >*/
  {
    if(keypress == KEY_NONE) return;
    keypress = KEY_NONE;
  }
}




static uint8_t ScanKey(void)
{
  for(uint8_t index =  0; index < 4; index++)
  {
    if(HAL_GPIO_ReadPin(GPIO_PORT[index], GPIO_PIN[index]) == GPIO_PIN_RESET)
    {
      return index + 1;
    }
  }
  return KEY_NONE;
}

static uint32_t keypad_GetTick(void)
{
  return HAL_GetTick();
}
