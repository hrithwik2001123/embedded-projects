#include "i2c-lcd.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;
static uint8_t LCD_ADDRESS = LCD_ADDRESS_1; // Start with 0x27

// Add backlight control
void lcd_backlight(uint8_t state) {
    uint8_t data = state ? 0x08 : 0x00;
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS, &data, 1, 100);
}

void lcd_send_cmd(char cmd) {
    uint8_t data_u, data_l;
    uint8_t data_t[4];

    data_u = (cmd & 0xF0) | 0x04;  // EN=1, RS=0, Backlight=1
    data_l = ((cmd << 4) & 0xF0) | 0x04;

    data_t[0] = data_u | 0x04;  // EN=1
    data_t[1] = data_u & ~0x04; // EN=0
    data_t[2] = data_l | 0x04;  // EN=1
    data_t[3] = data_l & ~0x04; // EN=0

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS, data_t, 4, 100);
}

void lcd_send_data(char data) {
    uint8_t data_u, data_l;
    uint8_t data_t[4];

    data_u = (data & 0xF0) | 0x05;  // EN=1, RS=1, Backlight=1
    data_l = ((data << 4) & 0xF0) | 0x05;

    data_t[0] = data_u | 0x04;  // EN=1
    data_t[1] = data_u & ~0x04; // EN=0
    data_t[2] = data_l | 0x04;  // EN=1
    data_t[3] = data_l & ~0x04; // EN=0

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDRESS, data_t, 4, 100);
}

void lcd_init(void) {
    HAL_Delay(50);

    // Try both addresses if needed
    if (HAL_I2C_IsDeviceReady(&hi2c1, LCD_ADDRESS_1 << 1, 3, 100) != HAL_OK) {
        LCD_ADDRESS = LCD_ADDRESS_2;
    }

    lcd_backlight(1); // Turn on backlight

    // 4-bit initialization sequence
    uint8_t init_sequence[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01};
    uint8_t delays[] = {5, 1, 1, 1, 1, 1, 1, 2};

    for (int i = 0; i < sizeof(init_sequence); i++) {
        lcd_send_cmd(init_sequence[i]);
        HAL_Delay(delays[i]);
    }

    HAL_Delay(10);
    lcd_clear();
}
