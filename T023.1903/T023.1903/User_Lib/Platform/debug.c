/** @file    debug.c
  * @author  minhneo
  * @website git/minhngocha
  * @ide     Keil uVision
  * @brief   debug library for STM32
  */
#include "debug.h"
#include "usart.h"
/*********************************************************************************
 * DEFNIE
 */
#define MAX_BUF_SIZE                                        128
#define NV200

#ifdef NV200
#define DEBUG_COLOR
#define DEBUG_CLEAR
#endif
/*********************************************************************************
 * GLOBAL FUNCTION
 */
 
char buf_debug[MAX_BUF_SIZE];
uint8_t len_debug;

/*********************************************************************************
 * STATIC VARIABLE
 */
static UART_HandleTypeDef*  DEBUG_PORT = &huart1;

/*********************************************************************************
 * EXPORTED FUNCTION
 */

/**
 * @brief 
 * 
 * @param
 * @retval
 */
void bdg_printf(uint8_t debug_level)
{
  #ifdef DEBUG_COLOR
  switch(debug_level)
  {
    case DEBUG_LEVEL_ERROR:                 /* Red text */
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[31m", 5 ,0x1000);
      break;
    case DEBUG_LEVEL_WARNING:               /* Yellow text */
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[33m", 5 ,0x1000);
      break;
    case DEBUG_LEVEL_INFO:                  /* White text */
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[37m", 5 ,0x1000);
      break;
    case DEBUG_COMMNET:                     /* Green text */
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[32m", 5 ,0x1000);
      break;
  }
  #endif
  switch(debug_level)
  {
    case DEBUG_LEVEL_ERROR:
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"ERROR: ", 7 ,0x1000);
      break;
    case DEBUG_LEVEL_WARNING:
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"WARNING: ", 9 ,0x1000);
      break;
    case DEBUG_LEVEL_INFO:
      HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"INFOR: ", 7 ,0x1000);
      break;
  }
  HAL_UART_Transmit(DEBUG_PORT, (uint8_t*)buf_debug, len_debug, 200);
}

/**
 * @brief 
 * 
 * @param
 * @retval
 */
void DEBUG_Clear(void)
{
  #ifdef DEBUG_CLEAR
  /* Clear Screen */
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[2J", 4 ,0x1000);
  /* Remove cursor */
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[H", 3 ,0x1000);
  #endif
}

/**
 * @brief 
 * 
 * @param
 * @retval
 */
void DEBUG_Start(void)
{
  #ifdef DEBUG_CLEAR
  /* Clear Screen */
  DEBUG_Clear();
  /* Reset special formatting */
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[H", 3 ,0x1000);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\033[0m",4, 0x1000);
  #endif
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"*******************************************\r\n", 45, 0x1000);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"****************@MinhNeo_TPA@**************\r\n", 45, 0x1000);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"*******************************************\r\n", 45, 0x1000);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"Author: @git/ngocminhha  minh.hn@tpa.com.vn\r\n", 45, 0x1000);
  len_debug = sprintf(buf_debug, "Compiled: %s %s\r\n", __DATE__, __TIME__);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)buf_debug,len_debug,0x1000);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"Target: STM32F103C6T\r\n", 23, 0x1000);
  HAL_UART_Transmit(DEBUG_PORT,(uint8_t*)"\r\n", 2, 0x1000);
}

/* USER CODE END PFP */
