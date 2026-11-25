/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define BUTTON1_PIN GPIO_PIN_0
#define BUTTON2_PIN GPIO_PIN_1
#define BUTTON3_PIN GPIO_PIN_2

#define LED1_PIN GPIO_PIN_5
#define LED2_PIN GPIO_PIN_6
#define LED3_PIN GPIO_PIN_7

#define DEBOUNCE_DELAY 50

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* Main function */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
    // BUTTON 1 -> LED1
    if (HAL_GPIO_ReadPin(GPIOA, BUTTON1_PIN) == GPIO_PIN_RESET)
    {
      HAL_Delay(DEBOUNCE_DELAY);
      HAL_GPIO_WritePin(GPIOA, LED1_PIN, GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA, LED1_PIN, GPIO_PIN_RESET);
    }

    // BUTTON 2 -> LED2
    if (HAL_GPIO_ReadPin(GPIOA, BUTTON2_PIN) == GPIO_PIN_RESET)
    {
      HAL_Delay(DEBOUNCE_DELAY);
      HAL_GPIO_WritePin(GPIOA, LED2_PIN, GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA, LED2_PIN, GPIO_PIN_RESET);
    }

    // BUTTON 3 -> LED3
    if (HAL_GPIO_ReadPin(GPIOA, BUTTON3_PIN) == GPIO_PIN_RESET)
    {
      HAL_Delay(DEBOUNCE_DELAY);
      HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA, LED3_PIN, GPIO_PIN_RESET);
    }
  }
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* GPIO Initialization */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();

  // Buttons as input (pull-up)
  GPIO_InitStruct.Pin = BUTTON1_PIN | BUTTON2_PIN | BUTTON3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // LEDs as output
  GPIO_InitStruct.Pin = LED1_PIN | LED2_PIN | LED3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* Error Handler */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
    // Stay here
  }
}
