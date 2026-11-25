#include <lpc214x.h>
#define PCLK 60000000
#define RS (1 << 16) // P0.16
#define RW (1 << 17) // P0.17
#define E  (1 << 18) // P0.18
int i;

void delay() {
    for (i = 0; i < 3000; i++); // Simple delay
}

void pll_in() {
    PLL0CON = 0x01;       // Enable PLL
    PLL0CFG = 0x24;       // Set multiplier and divider
    PLL0FEED = 0xAA;      // Feed sequence
    PLL0FEED = 0x55;
    while (!(PLL0STAT & (1 << 10))); // Wait for PLL to lock
    PLL0CON = 0x03;       // Connect PLL
    PLL0FEED = 0xAA;      // Feed sequence
    PLL0FEED = 0x55;
    VPBDIV = 0x01;        // Set PCLK = CCLK
}

void sendNibble(char nibble) {
    IOPIN0 = (IOPIN0 & 0xFFFFF00F) | ((nibble & 0xF0) << 4); // Send higher nibble
    IOSET0 = E;
    delay();
    IOCLR0 = E;
}

void command(char cmd) {
    IOCLR0 = RS | RW; // RS=0, RW=0 for command
    sendNibble(cmd & 0xF0);      // Higher nibble
    sendNibble(cmd << 4);        // Lower nibble
    delay();
}

void data(char data) {
    IOSET0 = RS;   // RS=1 for data
    IOCLR0 = RW;   // RW=0 for write
    sendNibble(data & 0xF0);     // Higher nibble
    sendNibble(data << 4);       // Lower nibble
    delay();
}

void lcdinit() {
    command(0x02); // Initialize in 4-bit mode
    command(0x28); // 4-bit mode, 2 lines, 5x7 font
    command(0x0C); // Display ON, Cursor OFF
    command(0x01); // Clear display
    command(0x80); // Set cursor to the beginning
}

void printString(char *str) {
    while (*str) {
        data(*str++);
    }
}

int main() {
    PINSEL0 = 0x00000000; // Set P0.0 to P0.15 as GPIO
    IODIR0 = 0x0001FF00;  // Set P0.8 to P0.15 as output for LCD
    lcdinit();            // Initialize LCD
    printString("Hello ARM"); // Print string on LCD
    while (1);
}
