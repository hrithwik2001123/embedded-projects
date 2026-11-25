#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h"
#include "lcd_i2c.h"

// Add these includes for ADC and IWDG
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_iwdg.h"

// Extern handles
extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc1;
extern IWDG_HandleTypeDef hiwdg;

// Function prototypes
void SystemClock_Config(void);
void Error_Handler(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_ADC1_Init(void);
void MX_IWDG_Init(void);
void UpdateTankStatus(void);

#endif /* __MAIN_H */