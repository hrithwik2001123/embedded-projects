/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : I2C LCD 16x2 with STM32F401CCU6
  * @attention
  * PB6 = I2C1_SCL, PB7 = I2C1_SDA
  * LCD I2C address: 0x27 (shifted left = 0x4E)
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* Private defines -----------------------------------------------------------*/
#define LCD_ADDR (0x27 << 1) // PCF8574 default address, shifted
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_COMMAND 0x00
#define LCD_DATA 0x01

/* Function prototypes -------------------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
void LCD_Init(void);
void LCD_SendCommand(uint8_t);
void LCD_SendData(uint8_t);
void LCD_SendByte(uint8_t, uint8_t);
void LCD_SendNibble(uint8_t);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);

/* Main Function -------------------------------------------------------------*/
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();

  LCD_Init();
  LCD_SetCursor(0, 0);
  LCD_Print("Welcome Hrithwik!");

  while (1)
  {
    // main loop
  }
}

/* LCD Functions -------------------------------------------------------------*/

void LCD_SendNibble(uint8_t nibble)
{
  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &nibble, 1, HAL_MAX_DELAY);
  HAL_Delay(1);
}

void LCD_SendByte(uint8_t byte, uint8_t mode)
{
  uint8_t high_nibble = (byte & 0xF0) | LCD_BACKLIGHT | mode;
  uint8_t low_nibble = ((byte << 4) & 0xF0) | LCD_BACKLIGHT | mode;

  // Send high nibble
  LCD_SendNibble(high_nibble | LCD_ENABLE);
  LCD_SendNibble(high_nibble);

  // Send low nibble
  LCD_SendNibble(low_nibble | LCD_ENABLE);
  LCD_SendNibble(low_nibble);
}

void LCD_SendCommand(uint8_t cmd)
{
  LCD_SendByte(cmd, LCD_COMMAND);
}

void LCD_SendData(uint8_t data)
{
  LCD_SendByte(data, LCD_DATA);
}

void LCD_Init(void)
{
  HAL_Delay(50);
  LCD_SendCommand(0x33); // Initialization
  LCD_SendCommand(0x32); // 4-bit mode
  LCD_SendCommand(0x28); // 2 lines, 5x8 font
  LCD_SendCommand(0x0C); // Display ON, Cursor OFF
  LCD_SendCommand(0x06); // Entry mode
  LCD_SendCommand(0x01); // Clear display
  HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
  uint8_t row_offsets[] = {0x00, 0x40};
  LCD_SendCommand(0x80 | (col + row_offsets[row]));
}

void LCD_Print(char *str)
{
  while (*str)
  {
    LCD_SendData(*str++);
  }
}

/* Peripheral Initialization -------------------------------------------------*/

static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* System Clock Config -------------------------------------------------------*/

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* Error Handler -------------------------------------------------------------*/

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
