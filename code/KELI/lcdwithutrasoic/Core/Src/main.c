#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

/* LCD Control Pins */
#define RS_PORT GPIOA
#define RS_PIN  GPIO_PIN_0
#define EN_PORT GPIOA
#define EN_PIN  GPIO_PIN_1

/* LCD Data Pins */
#define D4_PORT GPIOA
#define D4_PIN  GPIO_PIN_2
#define D5_PORT GPIOA
#define D5_PIN  GPIO_PIN_3
#define D6_PORT GPIOA
#define D6_PIN  GPIO_PIN_4
#define D7_PORT GPIOA
#define D7_PIN  GPIO_PIN_5

/* Ultrasonic Pins */
#define TRIG_PIN GPIO_PIN_7
#define ECHO_PIN GPIO_PIN_6

/* LCD Commands */
#define LCD_CLEAR 0x01
#define LCD_HOME  0x02
#define LCD_ENTRYMODE 0x06
#define LCD_DISPLAYON 0x0C
#define LCD_FUNCTIONSET 0x28

TIM_HandleTypeDef htim1; // Timer 1 for ultrasonic timing
void MX_GPIO_Init(void);
void MX_TIM1_Init(void);

void LCD_Enable(void);
void LCD_Send4Bit(uint8_t data);
void LCD_Command(uint8_t cmd);
void LCD_Write_Char(char data);
void LCD_Write_String(char *str);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Init(void);
float Get_Distance(void);

void LCD_Enable(void) {
    HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1); 
    HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_RESET);
}

void LCD_Send4Bit(uint8_t data) {
    HAL_GPIO_WritePin(D4_PORT, D4_PIN, (data & 0x01));
    HAL_GPIO_WritePin(D5_PORT, D5_PIN, (data & 0x02));
    HAL_GPIO_WritePin(D6_PORT, D6_PIN, (data & 0x04));
    HAL_GPIO_WritePin(D7_PORT, D7_PIN, (data & 0x08));
    LCD_Enable();
}

void LCD_Command(uint8_t cmd) {
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_RESET);
    LCD_Send4Bit(cmd >> 4); 
    LCD_Send4Bit(cmd & 0x0F);
}

void LCD_Write_Char(char data) {
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_SET);
    LCD_Send4Bit(data >> 4); 
    LCD_Send4Bit(data & 0x0F);
}

void LCD_Write_String(char *str) {
    while (*str) {
        LCD_Write_Char(*str++);
    }
}

void LCD_Set_Cursor(uint8_t row, uint8_t col) {
    if (row == 1)
        LCD_Command(0x80 + (col - 1));
    else if (row == 2)
        LCD_Command(0xC0 + (col - 1));
}

void LCD_Init(void) {
    HAL_GPIO_WritePin(RS_PORT, RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(EN_PORT, EN_PIN, GPIO_PIN_RESET);

    HAL_Delay(20);
    LCD_Send4Bit(0x03);
    HAL_Delay(5);
    LCD_Send4Bit(0x03);
    HAL_Delay(1);
    LCD_Send4Bit(0x03);
    LCD_Send4Bit(0x02);

    LCD_Command(LCD_FUNCTIONSET);
    LCD_Command(LCD_DISPLAYON);
    LCD_Command(LCD_CLEAR);
    LCD_Command(LCD_ENTRYMODE);
}

/* Ultrasonic Distance Calculation */
float Get_Distance(void) {
    uint32_t time;
    float distance;

    HAL_GPIO_WritePin(GPIOA, TRIG_PIN, GPIO_PIN_SET);
    HAL_Delay(1); 
    HAL_GPIO_WritePin(GPIOA, TRIG_PIN, GPIO_PIN_RESET);

    while (!HAL_GPIO_ReadPin(GPIOA, ECHO_PIN));
    __HAL_TIM_SET_COUNTER(&htim1, 0);

    while (HAL_GPIO_ReadPin(GPIOA, ECHO_PIN)) {
        time = __HAL_TIM_GET_COUNTER(&htim1);
    }

    distance = (time * 0.0343) / 2; // Convert time to cm
    return distance;
}

/* Main Code */
int main(void) {
    HAL_Init();
    MX_GPIO_Init();
    MX_TIM1_Init();
    HAL_TIM_Base_Start(&htim1);
    LCD_Init();

    LCD_Set_Cursor(1, 1);
    LCD_Write_String("Distance: ");

    while (1) {
        float distance = Get_Distance();
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%.2f cm", distance);

        LCD_Command(LCD_CLEAR);
        LCD_Set_Cursor(2, 1);
        LCD_Write_String(buffer);

        HAL_Delay(500);
    }
}

/* GPIO Configuration */
void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Trigger Pin - Output */
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Echo Pin - Input */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* Timer Configuration */
void MX_TIM1_Init(void) {
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 84-1;  // 1µs tick with 84MHz clock
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim1);
}
