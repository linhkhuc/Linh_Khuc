/** @file    ds18b20.h
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

#ifndef __DS18B20_H_
#define __DS18B20_H_
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

/**
* @defgroup  GROUP SIZE MAX BUFFER
* @brief
*/

/***********************************************************************
* TYPEDEF
*/

/*********************************************************************************
* STATIC VARIABLE
*/

/**
  * @brief  DS18B20 Status enumeration
  */
typedef enum
{
  DS18B20_OK,
  DS18B0_ERROR,
}ds18b20Status_t;
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
ds18b20Status_t DS18B20_Init(void);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void DS18B20_ReadTempratureU(uint16_t* pData);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void DS18B20_ReadTempratureF(float* pData);

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void DS18B20_Process(void);
#endif /* __DS18B20_H_ */
