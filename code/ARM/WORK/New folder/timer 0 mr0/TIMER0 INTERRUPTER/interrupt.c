#include <lpc214x.h>
# define PCLK 60000000
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
void myISR(void)__irq
		
			{
				 IOSET0 = 0xFFFFFFFF; // Turn on all pins of Port 0
				T0IR=0X01;
			VICVectAddr=0;
			
		}
		
void delay() {
		
    // Configure Timer0 for delay
		
    T0CTCR = 0x00;         // Timer mode
    T0TCR = 0x00;         // Reset timer
    T0PR = 59999;         // Prescale value for 1ms delay
    T0TCR = 0x01; 	// Start timer
		T0MR0=1000;
		T0MCR=(1<<0);
   while(T0TC!=T0MR0);    // Wait until delay time has elapsed
    T0TCR = 0x00;         // Stop timer
    T0TC = 0;             // Reset timer counter
}
int main() {
    pll_in();             // Initialize PLL
    PINSEL0 = 0x00000000; // Set all pins as GPIO
    IODIR0 = 0xFFFFFFFF;  // Set all pins of Port 0 as output
		VICIntSelect=(0<<4);
		VICIntEnable=(1<<4);
	  VICVectCntl1=(1<<5)|4;
		VICVectAddr1=(unsigned)myISR;
		delay();
    while (1);
}
