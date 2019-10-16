/** @file    ledSeg.h
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

#ifndef  __LEGSEG_H__
#define  __LEGSEG_H__
/*********************************************************************************
 * INCLUDE
 */
 
/* C Library */
#include "stdint.h"

/* Sys Library */
#include "gpio.h"

/* User Library */

/*********************************************************************************
* DEFINE
*/

#define BLINK_START                                         0xFF
#define BLINK_STOP                                          0x00
/***********************************************************************
* TYPEDEF
*/

/**
  * @brief  Led Function Status structures definition
  */
typedef enum{
  LED_InitOk,
  LED_Error,
}legStatus_t;
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
legStatus_t Led_Init(void);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_Process(void);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_SetBlink(uint8_t index);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_UpdateSetupValue(float value);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_UpdateTemperatureValue(float value);

#endif /* __LEGSEG_H__ */
