#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f4xx_hal.h"

// LCD Commands
#define LCD_CLEAR_DISPLAY   0x01
#define LCD_RETURN_HOME     0x02
#define LCD_ENTRY_MODE_SET  0x04
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CURSOR_SHIFT    0x10
#define LCD_FUNCTION_SET    0x20
#define LCD_SET_CGRAM_ADDR  0x40
#define LCD_SET_DDRAM_ADDR  0x80

// Function prototypes
void LCD_I2C_Init(I2C_HandleTypeDef *hi2c, uint8_t lcd_addr, uint8_t cols, uint8_t rows);
void LCD_I2C_WriteCommand(I2C_HandleTypeDef *hi2c, uint8_t cmd);
void LCD_I2C_WriteData(I2C_HandleTypeDef *hi2c, uint8_t data);
void LCD_I2C_WriteString(I2C_HandleTypeDef *hi2c, char *str);
void LCD_I2C_SetCursor(I2C_HandleTypeDef *hi2c, uint8_t col, uint8_t row);

#endif