#include "stm32f4xx_hal.h"

#define RS_PIN GPIO_PIN_0  // RS -> A0
#define E_PIN  GPIO_PIN_1  // Enable -> A1
#define D4_PIN GPIO_PIN_2  // Data 4 -> A2
#define D5_PIN GPIO_PIN_3  // Data 5 -> A3
#define D6_PIN GPIO_PIN_4  // Data 6 -> A4
#define D7_PIN GPIO_PIN_5  // Data 7 -> A5

#define LCD_PORT GPIOA  // Using GPIOA for LCD control

void LCD_Send_Cmd(uint8_t cmd);
void LCD_Send_Data(uint8_t data);
void LCD_Init(void);
void LCD_Send_String(char *str);
void LCD_Send_4Bits(uint8_t data);
void LCD_Enable(void);
void delay_ms(uint16_t ms);

void LCD_Init(void) {
    HAL_Delay(50); // LCD Power-up delay

    LCD_Send_Cmd(0x33); // Initialize LCD in 8-bit mode
    LCD_Send_Cmd(0x32); // Switch to 4-bit mode
    LCD_Send_Cmd(0x28); // Function set: 4-bit, 2 lines, 5x7 font
    LCD_Send_Cmd(0x0C); // Display ON, Cursor OFF
    LCD_Send_Cmd(0x06); // Entry mode set: Move cursor right
    LCD_Send_Cmd(0x01); // Clear display
    HAL_Delay(5);
}

void LCD_Send_Cmd(uint8_t cmd) {
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_RESET); // RS = 0 for command
    LCD_Send_4Bits(cmd >> 4);
    LCD_Send_4Bits(cmd & 0x0F);
}

void LCD_Send_Data(uint8_t data) {
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_SET); // RS = 1 for data
    LCD_Send_4Bits(data >> 4);
    LCD_Send_4Bits(data & 0x0F);
}

void LCD_Send_4Bits(uint8_t data) {
    HAL_GPIO_WritePin(LCD_PORT, D4_PIN, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_PORT, D5_PIN, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_PORT, D6_PIN, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_PORT, D7_PIN, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    LCD_Enable();
}

void LCD_Enable(void) {
    HAL_GPIO_WritePin(LCD_PORT, E_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, E_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

void LCD_Send_String(char *str) {
    while (*str) {
        LCD_Send_Data(*str++);
    }
}

void delay_ms(uint16_t ms) {
    HAL_Delay(ms);
}

int main(void) {
    HAL_Init();
    
    // Enable GPIOA Clock
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = RS_PIN | E_PIN | D4_PIN | D5_PIN | D6_PIN | D7_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);

    LCD_Init();
    LCD_Send_String("Hello, STM32!");

    while (1) {
        HAL_Delay(1000);
    }
}
