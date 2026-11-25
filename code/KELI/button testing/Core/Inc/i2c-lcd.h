#ifndef I2C_LCD_H
#define I2C_LCD_H

#include "stm32f4xx_hal.h"

// Try both common addresses if unsure
#define LCD_ADDRESS_1 0x27
#define LCD_ADDRESS_2 0x3F

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_put_cur(int row, int col);
void lcd_clear(void);
void lcd_backlight(uint8_t state);

#endif
