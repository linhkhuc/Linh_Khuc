/** @file    App.c
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
#include "tim.h"
/* User Library */
#include "app.h"
#include "ds18b20.h"
#include "keypad.h"
#include "ledSeg.h"
#include "..\User_Lib\pid\pid.h"
/*********************************************************************************
* DEFINE
*/

/***********************************************************************
* TYPEDEF
*/

/*********************************************************************************
* STATIC VARIABLE
*/
float gTemperatureRead = 0;
float gTemperatureSet = 0;

uint16_t gTemperatureSetBuf = 0;
uint8_t gStatusSetting = 0;

float Kp, Ki, Kd, setSampleTime;
/*********************************************************************************
 * STATIC FUNCTION
 */
static void Keypad_Handler(key_event_t event, uint8_t Keycode);
/*********************************************************************************
 * GLOBAL FUNCTION
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Ngat hien thi Led */
  if(htim->Instance == TIM4)
  {
    Led_Process();
    return;
  }
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
void App_Init(void)
{
  /* Init Led 7 seg */
  Led_Init();
  
  /* Init Keypad */
  Keypad_Init();
  
  /* Add Keypad Callback */
  Keypad_InstallCallback(KEY_HOLD,  Keypad_Handler);
  Keypad_InstallCallback(KEY_PRESS, Keypad_Handler);
  
  /* Khoi tao timer dieu khien PWM */
	HAL_TIM_Base_Start_IT(&htim1);
  
  /* Khoi tao timer hien thi LED7SEG*/
  HAL_TIM_Base_Start_IT(&htim4);
  
  /* Cai dat gia tri ban dau */
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void App_Step(void)
{
  /* Process Keypad */
  Keypad_Process();
  
  /* Process DS18B20 */
  DS18B20_Process();
  
  /* Get temperature */
  DS18B20_ReadTempratureF(&gTemperatureRead);
  
  /* Hien thi gia tri nhiet do hien tai */
  Led_UpdateTemperatureValue(gTemperatureRead);
  
  /* Che do dieu khien ON/OFF */
  if(gTemperatureRead > gTemperatureSet )
  {
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
    /* */
  }
  else if(gTemperatureRead < gTemperatureSet)
  {
    /* */
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
  }
	/* Che do dieu khien PID */
	
	PID_Controller(Kp, Ki, Kd, gTemperatureSet, setSampleTime);
}

static void Keypad_Handler(key_event_t event, uint8_t Keycode)
{
  if(event == KEY_PRESS)
  {
    /* Neu phim nhan la OK */
    if(Keycode == KEY_OK)
    {
      if(gStatusSetting == 0x00)
      {
        gStatusSetting = 0x01;
        gTemperatureSetBuf = gTemperatureSet * 10;
        Led_UpdateSetupValue(gTemperatureSetBuf);
        Led_SetBlink(BLINK_START);
      }
      else if(gStatusSetting == 0x01)
      {
        gStatusSetting = 0x00;
        gTemperatureSet = ((float) (gTemperatureSetBuf) / 10.0);
        Led_UpdateSetupValue(gTemperatureSet);
        Led_SetBlink(BLINK_STOP);
      }
      return;
    }
    
    /* Neu phim nhan la Exit */
    if(Keycode == KEY_EXIT)
    {
      if(gStatusSetting == 0x01)
      {
        gStatusSetting = 0x00;
        Led_UpdateSetupValue(gTemperatureSet);
        Led_SetBlink(BLINK_STOP);
      }
      return;
    }
  }
  
  if(event == KEY_PRESS || event == KEY_HOLD)
  {
    /* Neu phim nhan la UP */
    if(Keycode == KEY_UP)
    {
      /* Thay doi gia tri set */
      if(gStatusSetting == 0x01)
      {
        gTemperatureSetBuf += 1;
        if(gTemperatureSetBuf >= 800) gTemperatureSetBuf = 800;
        
        /* Cap nhat gia tri set */
        Led_UpdateSetupValue(gTemperatureSetBuf);
      }
      return;
    }
    
    /* Neu phim nhan la DOWN */
    if(Keycode == KEY_DOWN)
    {
      /* Thay doi gia tri set */
      if(gStatusSetting == 0x01)
      {
        gTemperatureSetBuf -= 1;
        if(gTemperatureSetBuf >= 100) gTemperatureSetBuf = 100;
        
        /* Cap nhat gia tri set */
        Led_UpdateSetupValue(gTemperatureSetBuf);
      }
      return;
    }
  }
}
