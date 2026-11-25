#include <lpc214x.h>

void pll_in() {
    // Configure PLL for desired frequency
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

void delay(int d) {
    // Configure Timer0 for delay
    T0CTCR = 0x0;         // Timer mode
    T0TCR = 0x02;         // Reset timer
    T0PR = 59999;         // Prescale value for 1ms delay
    T0TCR = 0x01;         // Start timer
    while (T0TC < d);     // Wait until delay time has elapsed
    T0TCR = 0x00;         // Stop timer
    T0TC = 0;             // Reset timer counter
}

int main() {
    pll_in();             // Initialize PLL
    PINSEL0 = 0x00000000; // Set all pins as GPIO
    PINSEL1 = 0x00000000;
    IODIR0 = 0xFFFFFFFF;  // Set all pins of Port 0 as output
    IODIR1 = 0xFFFFFFFF;  // Set all pins of Port 1 as output

    while (1) {
        IOSET0 = 0xFFFFFFFF; // Turn on all pins of Port 0
        IOSET1 = 0xFFFFFFFF; // Turn on all pins of Port 1
        delay(1000);         // Delay of 1000ms (1 second)
        IOCLR0 = 0xFFFFFFFF; // Turn off all pins of Port 0
        IOCLR1 = 0xFFFFFFFF; // Turn off all pins of Port 1
        delay(1000);         // Delay of 1000ms (1 second)
    }
}
