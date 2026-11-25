#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <stdio.h>  // For snprintf
#include <string.h> // For strlen
#include "stm32f4xx_hal.h"

// LCD Commands

// LCD Commands (adjust values as needed)
#define LCD_CLEAR_DISPLAY    0x01
#define LCD_RETURN_HOME      0x02
#define LCD_ENTRY_MODE_SET   0x04
#define LCD_DISPLAY_CONTROL  0x08
#define LCD_FUNCTION_SET     0x20
#define LCD_SET_DDRAM_ADDR   0x80
// ... (other commands)

// Function prototypes
void LCD_I2C_Init(I2C_HandleTypeDef *hi2c, uint8_t lcd_addr, uint8_t cols, uint8_t rows);
void LCD_I2C_Clear(I2C_HandleTypeDef *hi2c);
void LCD_I2C_WriteString(I2C_HandleTypeDef *hi2c, char *str);
void LCD_I2C_SetCursor(I2C_HandleTypeDef *hi2c, uint8_t col, uint8_t row);
// Add this with other function declarations
void LCD_I2C_WriteNumber(I2C_HandleTypeDef *hi2c, uint16_t num);
// ... (other function prototypes)

#endif