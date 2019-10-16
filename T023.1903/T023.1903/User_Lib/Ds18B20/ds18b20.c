/** @file    ds18b20.c
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
#include "gpio.h"
#include <math.h>

/* Sys Library */
/* User Library */
#include "ds18b20.h"

/*********************************************************************************
* DEFINE
*/

/**
 * @brief Pin communication Ds18b20 define
 **/
#define DS18B20_PIN                                         GPIO_PIN_8
#define DS18B20_PORT                                        GPIOA

/***********************************************************************
* TYPEDEF
*/
typedef enum
{
  DS18B20_INIT = 0x00,
  DS18B20_CONVERT,
  DS18B20_READ,
}DS18B20ProcesStatus;

/*********************************************************************************
* STATIC VARIABLE
*/
static GPIO_InitTypeDef GPIO_InitDS18B20Struct;
static uint32_t g_tick = 0;
uint8_t g_status = DS18B20_INIT;
uint16_t g_utemperature = 0x00;
float g_ftemperature = 0.0;
/*********************************************************************************
* STATIC FUNCTION
*/

static void gpio_set_input(void);
static void gpio_set_output(void);
static void ds18b20_writeByte(uint8_t data);
static uint8_t ds18b20_readByte(void);

__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
  micros *= (SystemCoreClock / 1000000) / 9;
  while(micros--);
}
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
ds18b20Status_t DS18B20_Init(void)
{
  gpio_set_output();                                                      // Set mode output
  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);           // Pull the pin low
  DelayMicro(500);
  
  gpio_set_input();                                                      // Set mode input
  DelayMicro(80);
  
  if(!HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
  {
    DelayMicro(400);
    return DS18B20_OK;
  }
  else
  {
    DelayMicro(400);
    return DS18B0_ERROR;
  }
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void DS18B20_ReadTempratureU(uint16_t* pData)
{
  *pData = g_utemperature;
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void DS18B20_ReadTempratureF(float* pData)
{
  /* init Variable */
  uint16_t mask = 0x01;
  g_ftemperature = 0.0;
  for(int8_t k = -4; k < 7; k++)
  {
    if (g_utemperature & mask) g_ftemperature += powf(2,k);
    mask = mask << 1;
  }
  *pData = g_utemperature;
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void DS18B20_Process(void)
{
  switch(g_status)
  {
    case DS18B20_INIT:
      if(DS18B20_Init() == DS18B20_OK)
      {
        g_status = DS18B20_CONVERT;
      }
      break;
      
    case DS18B20_CONVERT:
      ds18b20_writeByte(0xCC);
      ds18b20_writeByte(0x44);
      g_status = DS18B20_READ;
      g_tick = HAL_GetTick();
      break;
    
    case DS18B20_READ:
      if(HAL_GetTick() - g_tick > 800)
      {
        ds18b20_writeByte(0xCC);
        ds18b20_writeByte(0xBE);
        /* Read temperature */
        uint8_t temp_l = ds18b20_readByte();
        uint8_t temp_h = ds18b20_readByte();
        g_utemperature = (temp_h << 8) | temp_l;
        g_status = DS18B20_INIT;
      }
      break;
  }
}

static void gpio_set_input(void)
{
  GPIO_InitDS18B20Struct.Pin  = DS18B20_PIN;
  GPIO_InitDS18B20Struct.Mode = GPIO_MODE_INPUT;
  GPIO_InitDS18B20Struct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitDS18B20Struct);
}

static void gpio_set_output(void)
{
  GPIO_InitDS18B20Struct.Pin   = DS18B20_PIN;
  GPIO_InitDS18B20Struct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitDS18B20Struct.Pull  = GPIO_NOPULL;
  GPIO_InitDS18B20Struct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitDS18B20Struct);
}

static void ds18b20_writeByte(uint8_t data)
{
  /* Set output */
  gpio_set_output();
  
  for(uint8_t index = 0; index < 8 ; index++)
  {
    if(data & (0x01 << index))
    {
      gpio_set_output();
      HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
      DelayMicro(1);
      
      gpio_set_input();
      DelayMicro(60);
    }
    else
    {
      gpio_set_output();
      HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
      DelayMicro(60);
      
      gpio_set_input();
    }
  }
}

static uint8_t ds18b20_readByte(void)
{
  /* Inita variable */
  uint8_t value = 0;
  
  /* Set input */
  gpio_set_input();
  
  for(uint8_t index = 0; index < 8; index++)
  {
    gpio_set_output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    DelayMicro(2);
    
    gpio_set_input();
    DelayMicro(10);
    if(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))
    {
      value |= 0x01 << index;
    }
    DelayMicro(50);
  }
  return value;
}
