#include "stm32f4xx_hal.h"
#include "i2c-lcd.h"

I2C_HandleTypeDef hi2c1;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();

    // Initialize LCD with error handling
    lcd_init();
    lcd_clear();

    // Test display
    lcd_put_cur(0, 0);
    lcd_send_string("STM32 LCD Test");
    lcd_put_cur(1, 0);
    lcd_send_string("Address: 0x");
    lcd_send_string(LCD_ADDRESS == LCD_ADDRESS_1 ? "27" : "3F");

    while(1) {
        // Your application code
    }
}

void SystemClock_Config(void) {
    // Default HSI (16MHz) configuration
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();  // Enable GPIOB clock (for PB6/PB7)

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;  // PB6=SCL, PB7=SDA
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;         // Open-drain (required for I2C)
    GPIO_InitStruct.Pull = GPIO_PULLUP;             // Internal pull-up
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;      // Alternate function for I2C1
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void MX_I2C1_Init(void) {
    __HAL_RCC_I2C1_CLK_ENABLE();  // Enable I2C1 clock

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 50000;      // Reduced to 50kHz
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hi2c1);
}
