/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */
  GPIO_InitTypeDef gp;
  gp.Pin = GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_11;
  gp.Mode = GPIO_MODE_OUTPUT_PP;
  gp.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOE, &gp);

  gp.Pin = GPIO_PIN_6;
  gp.Mode = GPIO_MODE_INPUT;//input mode
  gp.Pull = GPIO_NOPULL;//浮空
  __HAL_RCC_GPIOE_CLK_ENABLE();
  HAL_GPIO_Init(GPIOE, &gp);
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_11, GPIO_PIN_SET);
  //HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //key未按下的情况，为高电平1
  unsigned int index = 0;
  unsigned int keyval = 1;
  unsigned int newkeyval = 1;
  //按照自己的思路来就行了

  while (1)
  {
	  newkeyval = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == GPIO_PIN_SET ? 1 : 0;
	  if(newkeyval == 0){
		  HAL_Delay(20);
		  while(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 0);
		  HAL_Delay(20);
		  switch(index % 3){
		  	  case 0:
		  	  	//HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
		  		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_SET);
		  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8,  GPIO_PIN_RESET);
		  	  	break;
		  	  case 1:
		  	  	//HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
		  		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8 | GPIO_PIN_11, GPIO_PIN_SET);
		  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10,  GPIO_PIN_RESET);
		  	  	break;
		  	  case 2:
		  	  	//HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
		  		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10 | GPIO_PIN_8, GPIO_PIN_SET);
		  		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11,  GPIO_PIN_RESET);
		  	  	break;
		  	  default:
		  	  	break;
		  	  }
		  index++;

	  }
	  HAL_Delay(1);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

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
