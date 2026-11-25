#include "lcd_i2c.h"
#include <string.h>
#include <stdio.h>

static I2C_HandleTypeDef *_lcd_i2c;

void lcd_send_cmd(char cmd) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xf0);
    data_l = ((cmd << 4) & 0xf0);
    data_t[0] = data_u | 0x0C;
    data_t[1] = data_u | 0x08;
    data_t[2] = data_l | 0x0C;
    data_t[3] = data_l | 0x08;
    HAL_I2C_Master_Transmit(_lcd_i2c, LCD_ADDR, data_t, 4, 100);
}

void lcd_send_data(char data) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xf0);
    data_l = ((data << 4) & 0xf0);
    data_t[0] = data_u | 0x0D;
    data_t[1] = data_u | 0x09;
    data_t[2] = data_l | 0x0D;
    data_t[3] = data_l | 0x09;
    HAL_I2C_Master_Transmit(_lcd_i2c, LCD_ADDR, data_t, 4, 100);
}

void lcd_init(I2C_HandleTypeDef *hi2c) {
    _lcd_i2c = hi2c;
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    lcd_send_cmd(0x20);  // 4-bit
    HAL_Delay(1);

    lcd_send_cmd(0x28); // 2 lines
    lcd_send_cmd(0x08); // display off
    lcd_send_cmd(0x01); // clear
    HAL_Delay(2);
    lcd_send_cmd(0x06); // entry mode
    lcd_send_cmd(0x0C); // display on
}

void lcd_send_string(char *str) {
    while (*str) lcd_send_data(*str++);
}

void lcd_put_cur(int row, int col) {
    switch (row) {
    case 0:
        lcd_send_cmd(0x80 + col);
        break;
    case 1:
        lcd_send_cmd(0xC0 + col);
        break;
    }
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}
