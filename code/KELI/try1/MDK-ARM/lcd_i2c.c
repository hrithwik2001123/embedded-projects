#include "lcd_i2c.h"
#include "main.h"
#include <string.h>

static uint8_t lcd_addr;
static uint8_t lcd_cols;
static uint8_t lcd_rows;

// Private function to send data/command
static void LCD_I2C_Write(I2C_HandleTypeDef *hi2c, uint8_t data, uint8_t mode) {
    uint8_t data_u, data_l;
    uint8_t data_arr[4];
    
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    
    data_arr[0] = data_u | mode | 0x04 | 0x08;  // en=1, rs=0
    data_arr[1] = data_u | mode | 0x00 | 0x08;  // en=0, rs=0
    data_arr[2] = data_l | mode | 0x04 | 0x08;  // en=1, rs=0
    data_arr[3] = data_l | mode | 0x00 | 0x08;  // en=0, rs=0
    
    HAL_I2C_Master_Transmit(hi2c, lcd_addr, data_arr, 4, 100);
    HAL_Delay(1);
}

// Public functions
void LCD_I2C_Init(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t cols, uint8_t rows) {
    lcd_addr = addr << 1;
    lcd_cols = cols;
    lcd_rows = rows;
    
    HAL_Delay(50);
    
    // Initialization sequence
    LCD_I2C_Write(hi2c, 0x30, 0);
    HAL_Delay(5);
    LCD_I2C_Write(hi2c, 0x30, 0);
    HAL_Delay(1);
    LCD_I2C_Write(hi2c, 0x30, 0);
    HAL_Delay(1);
    
    // Set 4-bit mode
    LCD_I2C_Write(hi2c, 0x20, 0);
    HAL_Delay(1);
    
    // Function set
    LCD_I2C_WriteCommand(hi2c, LCD_FUNCTION_SET | 0x08 | 0x04);
    HAL_Delay(1);
    
    // Display control
    LCD_I2C_WriteCommand(hi2c, LCD_DISPLAY_CONTROL | 0x04);
    HAL_Delay(1);
    
    // Clear display
    LCD_I2C_WriteCommand(hi2c, LCD_CLEAR_DISPLAY);
    HAL_Delay(2);
    
    // Entry mode set
    LCD_I2C_WriteCommand(hi2c, LCD_ENTRY_MODE_SET | 0x02);
    HAL_Delay(1);
}

void LCD_I2C_WriteCommand(I2C_HandleTypeDef *hi2c, uint8_t cmd) {
    LCD_I2C_Write(hi2c, cmd, 0);
}

void LCD_I2C_WriteData(I2C_HandleTypeDef *hi2c, uint8_t data) {
    LCD_I2C_Write(hi2c, data, 1);
}

void LCD_I2C_WriteString(I2C_HandleTypeDef *hi2c, char *str) {
    while (*str) {
        LCD_I2C_WriteData(hi2c, *str++);
    }
}

void LCD_I2C_SetCursor(I2C_HandleTypeDef *hi2c, uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (row >= lcd_rows) {
        row = lcd_rows - 1;
    }
    LCD_I2C_WriteCommand(hi2c, LCD_SET_DDRAM_ADDR | (col + row_offsets[row]));
}
void LCD_I2C_Clear(I2C_HandleTypeDef *hi2c) {
    LCD_I2C_WriteCommand(hi2c, 0x01); 
    HAL_Delay(2); 
}
