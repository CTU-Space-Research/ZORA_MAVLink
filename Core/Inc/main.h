/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define MAVLINK_MAX_MESSAGE_LENGTH 280

#define MAVLINK_USART1_CHANNEL_NUM MAVLINK_COMM_0

#define MAVlinkSystemID MAV_SYS_ROCKET
#define MAVlinkComponentID MAV_COMP_ID_ZORA_ENGINE

extern UART_HandleTypeDef huart1;

//we will store byte after byt to this FILO buffer
extern volatile uint8_t UART_RX_Buffer[MAVLINK_MAX_MESSAGE_LENGTH];
extern volatile uint16_t UART_RX_Buffer_NextFreeByteIndex;

//when the message is received whole, it will be copied to this buffer
extern volatile uint8_t UART_RX_Received_Message[MAVLINK_MAX_MESSAGE_LENGTH];
extern volatile uint16_t UART_RX_Received_NextFreeByteIndex;

extern volatile  uint8_t FLAG_UART_line_IDLE;

/*//wait until the usart TX buffer register is empty
    while( ( (*uart).Instance->ISR & USART_ISR_TXFE) != true){}*/


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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ORANGE_Pin GPIO_PIN_13
#define LED_ORANGE_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_12
#define LED_GREEN_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */
#include "MAVLinkImplementation.h"
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
