#include <lpc17xx.h>
#define PCLK 60000000

int i;
char ch;


void uart_in(unsigned int baudrate) {
    unsigned int DL;
    LPC_PINCON->PINSEL0 = 0x00000050; // Configure UART pins
    LPC_UART0->LCR = 0x83; // 8 bits, 1 stop bit, no parity, DLAB = 1
    DL = (PCLK / 16) / baudrate; // Calculate divisor
    LPC_UART0->DLM = DL >> 8; // Set DLM
    LPC_UART0->DLL = DL & 0xFF; // Set DLL
    LPC_UART0->LCR = 0x03; // DLAB = 0
}

int main() {
    uart_in(9600); // Initialize UART
    while (1) {
        while (!(LPC_UART0->LSR & (1 << 5))); // Wait for data to be received
        LPC_UART0->THR = 'G';// Echo received character
        for (i = 0; i < 1000; i++); // Simple delay
    }
}