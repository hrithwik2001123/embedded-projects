#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h"
#include "lcd_i2c.h"

// Extern I2C handle
extern I2C_HandleTypeDef hi2c1;

// Function prototypes
void SystemClock_Config(void);
void Error_Handler(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);

#endif /* __MAIN_H */