#include "main.h"

#define DEBOUNCE_DELAY_MS 50

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

GPIO_PinState readDebouncedButton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1)
    {
        if (readDebouncedButton(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        }

        if (readDebouncedButton(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
        }

        if (readDebouncedButton(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
        }
    }
}

GPIO_PinState readDebouncedButton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinState state1 = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
    HAL_Delay(DEBOUNCE_DELAY_MS);
    GPIO_PinState state2 = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);

    if (state1 == GPIO_PIN_RESET && state2 == GPIO_PIN_RESET) {
        return GPIO_PIN_RESET;
    } else {
        return GPIO_PIN_SET;
    }
}
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Buttons (Input with internal pull-up)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // LEDs (Output)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

