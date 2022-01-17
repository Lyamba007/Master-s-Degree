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
/* USER CODE BEGIN Private defines */
//********************************DEFINES REGION***********************************//
/*States definition with numbers coding (0-7)*/
typedef enum {a0,a1,a2,a3,a4,a5,a6,a7} States;

/*All delays in ms (0-5 + DELAYS_COUNT that shows the count of delays)*/
typedef enum {T0,T1,T2,T3,Tb,Tc,DELAYS_COUNT}Delays;

#define LEDS GPIOA /*LED control block (for simplicity)*/

/*All the LEDs that locates in LED control block*/
#define BTN_LIGHT				 			GPIO_PIN_3 
#define RED_LIGHT         		GPIO_PIN_4 	
#define LIGHTER				        GPIO_PIN_5 
#define C1   									GPIO_PIN_6
#define C2   									GPIO_PIN_7 	
#define C3 										GPIO_PIN_8
#define C4  									GPIO_PIN_9 
#define C5  									GPIO_PIN_10	
#define C6   									GPIO_PIN_11


#define ON  GPIO_PIN_SET	/*ON definition for LEDs and buttons*/
#define OFF GPIO_PIN_RESET	/*OFF definition for LEDs and buttons*/

/*Reset All LEDs (0 value on outputs)*/
#define ALL_LEDS_OFF HAL_GPIO_WritePin(GPIOA, BTN_LIGHT|RED_LIGHT|LIGHTER|C1|C2|C3|C4|C5|C6, GPIO_PIN_RESET);

#define BTN_READY 		HAL_NVIC_EnableIRQ(EXTI2_IRQn);  /*Событие нажатия кнопки перехода*/
#define BTN_NOT_READY HAL_NVIC_DisableIRQ(EXTI2_IRQn); /*Событие запрета нажатия кнопки перехода*/

#define BUTTON_ON HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) /*CHECK if the system is ON/OFF*/
#define BTN HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) /*CHECK if the btn is pushed*/

//******************************END DEFINES REGION*****************************//


//********************FUNCTION PROTOTYPES***********************//
void StateTransition(void); //Transition function
//*************************************************************//
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
