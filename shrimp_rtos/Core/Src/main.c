/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "relay.h"
#include "stdio.h"
#include "stdlib.h"
#include "ds18b20.h"
#include "motor.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "4gdtu.h"
#include "iwdg.h"
#include "sensor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char Tx[20];
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
/* USER CODE BEGIN PFP */
TaskHandle_t TaskDS18B20_Handle;
TaskHandle_t TaskTur_Handle;
TaskHandle_t TaskpH_Handle;
TaskHandle_t TaskTDS_Handle;
TaskHandle_t Task4GHandle;
TaskHandle_t TaskDoHandle;
extern QueueHandle_t uartQueue;
extern char receivedString[BUFFER_SIZE]; 

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void vApplicationIdleHook(void)
{

}

void vApplicationTickHook(void)
{

}

void vApplicationStackOverflowHook(TaskHandle_t xTask,char *pcTaskName)
{
	
}

void vApplicationMallocFailedHook (void)
{
	
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
  int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_TIM10_Init();
  MX_TIM6_Init();
	/* USER Init      */                   
	Pwm_Init();
	HAL_UART_INTERRUPT();
  HAL_TIM_Base_Init(&htim10);
	HAL_TIM_Base_Start_IT(&htim10);
	
	uartQueue=xQueueCreate(5, sizeof(receivedString));
	
	if(uartQueue==NULL)
	{
		sprintf(Tx,"Queue creat failed\n");
		HAL_UART_Transmit
		(&huart1,(uint8_t *)Tx,strlen(Tx),HAL_MAX_DELAY);
	}
	
	xTaskCreate(vTaskDS18B20Print,
						  "DS18B20",
							200,
							NULL,
							3,
							&TaskDS18B20_Handle
							);
	
	xTaskCreate(vTaskTur,
						  "TUR",
							200,
							NULL,
							3,
							&TaskTur_Handle
							);
	
	xTaskCreate(vTaskpH,
						  "pH",
							200,
							NULL,
							3,
							&TaskpH_Handle
							);
							
		xTaskCreate(vTaskTDS,
						  "TDS",
							200,
							NULL,
							3,
							&TaskTDS_Handle
							);						
	
//	xTaskCreate(vReceiveTask,
//						  "4G_RECEIVE",
//							1024,
//							NULL,
//							4,
//							&Task4GHandle
//	           );
	
//xTaskCreate(vReceiveQueueTask,
//						"4G_DO",
//						512,
//						NULL,
//						4,
//						&TaskDoHandle
//					 );
					 
	vTaskStartScheduler();            
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
