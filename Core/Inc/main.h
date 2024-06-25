/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define ImaliPOWER_Pin GPIO_PIN_4
#define ImaliPOWER_GPIO_Port GPIOE
#define ImaliPOWER_EXTI_IRQn EXTI4_IRQn
#define PowerSW_Key_0_Pin GPIO_PIN_5
#define PowerSW_Key_0_GPIO_Port GPIOE
#define PowerON_Pin GPIO_PIN_6
#define PowerON_GPIO_Port GPIOE
#define Flash1_CE_Pin GPIO_PIN_0
#define Flash1_CE_GPIO_Port GPIOC
#define Flash2_CE_Pin GPIO_PIN_1
#define Flash2_CE_GPIO_Port GPIOC
#define Flash_SPI2_MISO_Pin GPIO_PIN_2
#define Flash_SPI2_MISO_GPIO_Port GPIOC
#define Flash_SPI2_MOSI_Pin GPIO_PIN_3
#define Flash_SPI2_MOSI_GPIO_Port GPIOC
#define DriverUSART4_Tx_Pin GPIO_PIN_0
#define DriverUSART4_Tx_GPIO_Port GPIOA
#define Key_9_Pin GPIO_PIN_3
#define Key_9_GPIO_Port GPIOA
#define Key_4_Pin GPIO_PIN_4
#define Key_4_GPIO_Port GPIOA
#define Key_3_Pin GPIO_PIN_5
#define Key_3_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_6
#define Buzzer_GPIO_Port GPIOA
#define Key_2_Pin GPIO_PIN_7
#define Key_2_GPIO_Port GPIOA
#define Key_8_Pin GPIO_PIN_4
#define Key_8_GPIO_Port GPIOC
#define Key_7_Pin GPIO_PIN_5
#define Key_7_GPIO_Port GPIOC
#define IN_1_Pin GPIO_PIN_0
#define IN_1_GPIO_Port GPIOB
#define IN_1_EXTI_IRQn EXTI0_IRQn
#define IN_2_Pin GPIO_PIN_1
#define IN_2_GPIO_Port GPIOB
#define IN_2_EXTI_IRQn EXTI1_IRQn
#define Key_1_Pin GPIO_PIN_10
#define Key_1_GPIO_Port GPIOB
#define Key_6_Pin GPIO_PIN_11
#define Key_6_GPIO_Port GPIOB
#define Key_5_Pin GPIO_PIN_12
#define Key_5_GPIO_Port GPIOB
#define Flash_SPI2_SCK_Pin GPIO_PIN_13
#define Flash_SPI2_SCK_GPIO_Port GPIOB
#define LCD_Led_Pin GPIO_PIN_13
#define LCD_Led_GPIO_Port GPIOD
#define Key_11_Pin GPIO_PIN_6
#define Key_11_GPIO_Port GPIOC
#define Key_10_Pin GPIO_PIN_7
#define Key_10_GPIO_Port GPIOC
#define LCD_Reset_Pin GPIO_PIN_8
#define LCD_Reset_GPIO_Port GPIOA
#define GPS_Tx_Pin GPIO_PIN_9
#define GPS_Tx_GPIO_Port GPIOA
#define GPS_Rx_Pin GPIO_PIN_10
#define GPS_Rx_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
