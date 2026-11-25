#include "main.h"
#include "lcd_i2c.h"
#include "stm32f4xx_hal.h"
#include <string.h>  


// --- I2C Handle ---
I2C_HandleTypeDef hi2c1;

#define TANK_LOW_PIN      GPIO_PIN_0  // bottom sensor
#define TANK_HALF_PIN     GPIO_PIN_1  // middle sensor
#define TANK_FULL_PIN     GPIO_PIN_2  // top sensor
#define TANK_PORT GPIOA


#define DEBOUNCE_DELAY 50

// --- Function Prototypes ---
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void Error_Handler(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
 LCD_I2C_Init(&hi2c1, 0x27, 16, 2);
    LCD_I2C_Clear(&hi2c1);
    LCD_I2C_SetCursor(&hi2c1, 0, 0);
    LCD_I2C_WriteString(&hi2c1, "Tank Monitor Ready");

    HAL_Delay(200);
    LCD_I2C_Clear(&hi2c1);

    char lastMessage[17] = "";

    while (1)
    {
    uint8_t low = HAL_GPIO_ReadPin(TANK_PORT, TANK_LOW_PIN);
    uint8_t half = HAL_GPIO_ReadPin(TANK_PORT, TANK_HALF_PIN);
    uint8_t full = HAL_GPIO_ReadPin(TANK_PORT, TANK_FULL_PIN);
        LCD_I2C_Clear(&hi2c1);
        HAL_Delay(100);

     if (full == GPIO_PIN_RESET) {
        // If HIGH sensor is triggered, tank is full regardless of other sensors
        LCD_I2C_WriteString(&hi2c1, "Tank is Full");
    }
    else if (half == GPIO_PIN_RESET) {
        // If HALF sensor is triggered (but HIGH is not), tank is at least half
        LCD_I2C_WriteString(&hi2c1, "Tank is Half");
    }
    else if (low == GPIO_PIN_RESET) {
        // If only LOW sensor is triggered, tank is low
        LCD_I2C_WriteString(&hi2c1, "Tank is Low");
    }
    else {
        // No sensors triggered
        LCD_I2C_WriteString(&hi2c1, "Tank is Empty");
    }

    HAL_Delay(1000);
}
}

// --- I2C1 Init ---
void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }
}

// --- GPIO Init ---
void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // I2C GPIOB: PB6 (SCL), PB7 (SDA)
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Button Inputs (PA0, PA1, PA2)
    GPIO_InitStruct.Pin = TANK_LOW_PIN | TANK_HALF_PIN | TANK_FULL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// --- Error Handler ---
void Error_Handler(void) {
    while (1) {
        // Trap in error
    }
}

// --- Clock Config (stub or complete based on CubeMX) ---
void SystemClock_Config(void) {
    // Insert proper system clock config here or use CubeMX-generated version
}
