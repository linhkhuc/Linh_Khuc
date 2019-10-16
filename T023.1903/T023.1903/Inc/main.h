/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DLEG_1_Pin GPIO_PIN_0
#define DLEG_1_GPIO_Port GPIOA
#define DLEG_2_Pin GPIO_PIN_1
#define DLEG_2_GPIO_Port GPIOA
#define DLEG_3_Pin GPIO_PIN_2
#define DLEG_3_GPIO_Port GPIOA
#define DLEG_4__Pin GPIO_PIN_3
#define DLEG_4__GPIO_Port GPIOA
#define DLEG_5_Pin GPIO_PIN_4
#define DLEG_5_GPIO_Port GPIOA
#define DLEG_6_Pin GPIO_PIN_5
#define DLEG_6_GPIO_Port GPIOA
#define DLEG_7_Pin GPIO_PIN_6
#define DLEG_7_GPIO_Port GPIOA
#define DLEG_8_Pin GPIO_PIN_7
#define DLEG_8_GPIO_Port GPIOA
#define SLEG_1_Pin GPIO_PIN_0
#define SLEG_1_GPIO_Port GPIOB
#define SLEG_2_Pin GPIO_PIN_1
#define SLEG_2_GPIO_Port GPIOB
#define SLEG_3_Pin GPIO_PIN_2
#define SLEG_3_GPIO_Port GPIOB
#define SLEG_4_Pin GPIO_PIN_10
#define SLEG_4_GPIO_Port GPIOB
#define SLEG_5_Pin GPIO_PIN_11
#define SLEG_5_GPIO_Port GPIOB
#define SLEG_6_Pin GPIO_PIN_12
#define SLEG_6_GPIO_Port GPIOB
#define SLEG_7_Pin GPIO_PIN_13
#define SLEG_7_GPIO_Port GPIOB
#define SLEG_8_Pin GPIO_PIN_14
#define SLEG_8_GPIO_Port GPIOB
#define DATAIN_Pin GPIO_PIN_8
#define DATAIN_GPIO_Port GPIOA
#define DEBUG_TX_Pin GPIO_PIN_9
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_10
#define DEBUG_RX_GPIO_Port GPIOA
#define RELAY_Pin GPIO_PIN_11
#define RELAY_GPIO_Port GPIOA
#define UP_Pin GPIO_PIN_3
#define UP_GPIO_Port GPIOB
#define DOWN_Pin GPIO_PIN_4
#define DOWN_GPIO_Port GPIOB
#define OK_Pin GPIO_PIN_5
#define OK_GPIO_Port GPIOB
#define EXIT_Pin GPIO_PIN_6
#define EXIT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
