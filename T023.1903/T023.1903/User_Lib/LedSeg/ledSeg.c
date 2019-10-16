/** @file    ledseg.c
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
#include "ledseg.h"

/*********************************************************************************
* DEFINE
*/

/**
* @defgroup  GROUP NUMBER PIN DATA & PIN SELECT
* @brief
*/
#define DPIN_NUM                                            8
#define SPIN_NUM                                            8
#define NUM_LED_ROW                                         4
#define NUM_ALL_LED                                         8
/***********************************************************************
* TYPEDEF
*/

/*********************************************************************************
* STATIC VARIABLE
*/

/**
 * @brief Led 7 segment data port
 **/
static GPIO_TypeDef* GPIO_DPORT[DPIN_NUM] = {GPIOA};
  
/**
 * @brief Led 7 segment data pin
 **/
static const uint16_t GPIO_DPIN[DPIN_NUM] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};

/**
 * @brief Led 7 segment select port
 **/
static GPIO_TypeDef* GPIO_SPORT[DPIN_NUM] = {GPIOB};

/**
 * @brief Led 7 segment select pin
 **/
static const uint16_t GPIO_SPIN[DPIN_NUM] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14};


/**
 * @brief Led 7 code
 **/
static const uint8_t seg7Code[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};

/****************************************************/
/* |   0   |   1  |   2  |   3   |  ROW1 FOR SETUP  */ 
/* |   4   |   5  |   6  |   7   |  ROW2 FOR DISPLAY*/
volatile uint8_t ledSelectDisplay = 0;

/***********************************/
/* |   0   |   1  |   2  |   3   | */
/* | NONE  | LED1 | LED2 | LED3  | */
volatile uint8_t ledBlink = BLINK_STOP;

volatile uint16_t setValue;
volatile uint16_t temperatureValue;
/*********************************************************************************
 * STATIC FUNCTION
 */
static void led_DisplayCurrentTemperature(void);
static void led_DisplaySetTemperature(void);
static void led_Select(void);
static void led_OutData(uint8_t data);
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
legStatus_t Led_Init(void)
{
  return LED_InitOk;
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_Process(void)
{
  /* Chon led hien thi */
  led_Select();
  
  if(ledSelectDisplay < NUM_LED_ROW)
  {
    led_DisplaySetTemperature();
  }
  else
  {
    led_DisplayCurrentTemperature();
  }
  
  /* Tang chi so index led hien thi */
  ledSelectDisplay++;
  if(ledSelectDisplay >= NUM_ALL_LED) ledSelectDisplay = 0;
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_SetBlink(uint8_t index)
{
  ledBlink = index;
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_UpdateSetupValue(float value)
{
  setValue = (uint16_t) value;
}

/**
 * @brief
 * @author: minhneo
 * 
 * @param
 * @retval
 */
void Led_UpdateTemperatureValue(float value)
{
  temperatureValue = (uint16_t) value;
}


static void led_DisplayCurrentTemperature(void)
{
  switch(ledSelectDisplay)
  {
    case 4:
      led_OutData(temperatureValue / 1000);
      break;
    case 5:
      led_OutData(temperatureValue % 1000 / 100);
      break;
    case 6:
      led_OutData(temperatureValue % 100 / 10);
      break;
    case 7:
      led_OutData(temperatureValue % 10);
      break;
  }
}

static void led_DisplaySetTemperature(void)
{
  switch(ledSelectDisplay)
  {
    case 0:
      led_OutData(setValue / 1000);
      break;
    case 1:
      led_OutData(setValue % 1000 / 100);
      break;
    case 2:
      led_OutData(setValue % 100 / 10);
      break;
    case 3:
      led_OutData(setValue % 10);
      break;
  }
}

static void led_Select(void)
{
  /* Clear all select */
  for(uint8_t index = 0; index < NUM_ALL_LED; index++)
  {
    HAL_GPIO_WritePin(GPIO_SPORT[index], GPIO_SPIN[index], GPIO_PIN_RESET);
  }
  
  /* select pin */
  HAL_GPIO_WritePin(GPIO_SPORT[ledSelectDisplay], GPIO_SPIN[ledSelectDisplay], GPIO_PIN_RESET);
}

static void led_OutData(uint8_t data)
{
  uint8_t bufData = seg7Code[data];
  for(uint8_t index = 0; index < NUM_ALL_LED; index++)
  {
    HAL_GPIO_WritePin(GPIO_DPORT[index], GPIO_DPIN[index], (GPIO_PinState) (bufData & (0x01 >> index)));
  }
}
