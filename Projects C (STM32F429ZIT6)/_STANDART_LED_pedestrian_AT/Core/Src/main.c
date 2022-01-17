/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gfxsimulator.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t delays[DELAYS_COUNT] = {1000,3000,5000,5000,101,30000}; //Array with a delay values

/*
	Special variable for delay function to execute the transition a5-a4-a3-a6
	volatile specificator tells the program that 
	the variable value can be changed in another part of main program (e.g.interrupts)
	but the main cycle will know it
*/
volatile uint16_t walkTime;	

volatile States state = a0;	//Current state
States nextState;	  //Next state

//A special checkers for each pushed/unpushed button in system
//
volatile uint8_t isButtonOnPushed;
volatile uint8_t isBtnPushed;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_GFXSIMULATOR_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim3); //Allow to start the transition function
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		StateTransition(); //The function transition and outputs function working 
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
	* CubeMx generated function for enable all the peripheral events/interrupts in project
  */
static void MX_NVIC_Init(void)
{
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* EXTI1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);
  /* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* EXTI2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

/* USER CODE BEGIN 4 */
void StateTransition()
{
	//Transitions function 
	//
		switch(state) 			 
	{
		case a0: 		 /*Block with transition description*/
			
			if(isButtonOnPushed == 0)	/*BUTTON_ON push/unpush checker*/
			{
				nextState = a0;
			}
			
			else 
			{
				nextState = a1;
			}	
			
		break;
								
		case a1:
			
			if(isButtonOnPushed == 0)
			{
				nextState = a0;
			}
			
			else 
			{	
				if(isBtnPushed == 0) /*BTN push/unpush checker*/
				{
					nextState = a1;
				}
				
				else
				{
					nextState = a2;
				}
			}
			
		break;
			
		case a2:
				nextState = a3;
		break;	
				
		case a3:
			
				if(walkTime >= delays[T1]*4) /*Check the time in hyper process and select the right next state*/
				{
					nextState = a7;
				}
				
				else
				{
					nextState = a4;
				}
				
		break;
			
		case a4:
				nextState = a5;
		break;
				
		case a5:
				nextState = a6;
		break;
		
	  case a6:
			nextState = a3;
		break;
		
		case a7:
			nextState = a1;
		break;
				
		default: /*Default transition for insurance from exceptions*/
				nextState = a0;
		break;
	}

	switch(state)				/*Outputs function*/
	{	
		case a0: 	
     isBtnPushed = 0;	/*Hard reset for btn (to avoid the exceptions)*/
     ALL_LEDS_OFF;    /*OFF all the outputs in a model*/
		 BTN_NOT_READY; 	/*Forbid the interrupt handler (btn pushing is forbidden)*/
		break;
			
		case a1:
			
		 if(isBtnPushed == 0)
		 {
			BTN_READY; 			/*Allow the interrupt handler (push the btn)*/
			HAL_GPIO_WritePin(LEDS,BTN_LIGHT,ON); /*LED shows that the btn can be pushed*/ 
		 }			 
		 else
		 {
			BTN_NOT_READY;
			HAL_GPIO_WritePin(LEDS,BTN_LIGHT,OFF); /*OFF the btn pushing indication*/
		 }
		 
		break;	
		
	  case a2:
			
		 //Output delay that allows to operate with a red light and lighter at the certain time
		 //ON the red light and the lighter when the state time between 5 and 10 seconds of state
		 //
		 if(__HAL_TIM_GET_COUNTER(&htim3) > delays[T3]) 
		 {
			isBtnPushed = 0;
			HAL_GPIO_WritePin(LEDS,RED_LIGHT|LIGHTER,ON);		 
		 }	 
		break;	
		 
		/*Hyper States outputs blocks*/
		case a3:	
		 HAL_GPIO_WritePin(LEDS,C1|C6,ON);
		 HAL_GPIO_WritePin(LEDS,C2|C5,OFF);
		 HAL_GPIO_WritePin(LEDS,C3|C4,OFF);		
		break;
		
		case a4:
		 HAL_GPIO_WritePin(LEDS,C1|C6,OFF);
		 HAL_GPIO_WritePin(LEDS,C2|C5,ON);
		 HAL_GPIO_WritePin(LEDS,C3|C4,OFF);	
		break; 
			
		case a5:
		 HAL_GPIO_WritePin(LEDS,C1|C6,OFF);
		 HAL_GPIO_WritePin(LEDS,C2|C5,OFF);
		 HAL_GPIO_WritePin(LEDS,C3|C4,ON);		
		break;  
		
		case a6:
		 HAL_GPIO_WritePin(LEDS,C1|C6,OFF);
		 HAL_GPIO_WritePin(LEDS,C2|C5,ON);
		 HAL_GPIO_WritePin(LEDS,C3|C4,OFF);		
		break; 
	 /*END Hyper States outputs blocks*/	
		
		case a7:
			
			HAL_GPIO_WritePin(LEDS,C1|C6,OFF);
		
			if(__HAL_TIM_GET_COUNTER(&htim3) > delays[T3])
			{		
				HAL_GPIO_WritePin(LEDS,RED_LIGHT|LIGHTER,OFF);
				
				//COPY of a1 state that shows the ability to push the btn in a constraint time to the next state transition
				//
				if(isBtnPushed == 0)
				{
					BTN_READY; 		
					HAL_GPIO_WritePin(LEDS,BTN_LIGHT,ON); 
				}			 
				else
				{
					BTN_NOT_READY;
					HAL_GPIO_WritePin(LEDS,BTN_LIGHT,OFF); 
				}					
			}
			
		break;
		
		default: /*The default block for outputs (to avoid the exceptions)*/
     isBtnPushed = 0;	  		
     ALL_LEDS_OFF;        
		 BTN_NOT_READY; 
		break;
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) //Pushing button interrupt handler(callback)
{
	if(GPIO_Pin == GPIO_PIN_1 || GPIO_Pin == GPIO_PIN_2) //Check the correct pin (btn pin) for insurance 
	{
		HAL_TIM_Base_Start_IT(&htim4); //Allow the timer working for buttons 
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //Timer interrupt handler(callback)
{	
	//Delays function
	//
	if(htim->Instance == TIM3)
	{
		HAL_TIM_Base_Stop_IT(&htim3); //Stop the timer and forbid the interrupt (for insurance)
		
		uint16_t delayMs = 0;					//Variable for keeping the chosen delay
		
		state = nextState;						//Transition execution
		
		if(state == a0 || state == a1)
		{
			delayMs = delays[T0];
		}
		
		else if(state == a2)
		{
			delayMs = delays[T2]+delays[T3];			
		}
		
		else if(state == a3 || state == a4 || state == a5 || state == a6)
		{
			delayMs = delays[T1];
			walkTime += delays[T1];
		}
		
		else if(state == a7)
		{
			delayMs = delays[T3]+delays[Tc];
			walkTime = 0;
		}
		
		else //for insurance to avoid the  exceptions
		{
			delayMs = delays[T0];
		}
		
		__HAL_TIM_SET_AUTORELOAD(&htim3, delayMs); //Reload the necessary timeout to the timer register
		
		//The correct way in interrupt handling
		//is the stop and start the timer again (including interrupt handling)
		//		
		HAL_TIM_Base_Start_IT(&htim3); 
	}
	
	//Interrupt handler for BUTTON_ON and BTN
	//
	else if(htim->Instance == TIM4) 
	{
		if(BUTTON_ON == ON)
		{
			isButtonOnPushed = !isButtonOnPushed; //Change the value of pushing (like a toggle)
		}
		else if (BTN == ON)
		{
			isBtnPushed = 1;
		}
		else
		{
			isButtonOnPushed = 0;
			isBtnPushed = 0;
		}
	
		HAL_TIM_Base_Stop_IT(&htim4); //Stop the timer work for buttons
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
