#include <lpc214x.h>
# define PCLK 60000000
 unsigned int i;
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
			T0IR=0X01;
			VICVectAddr=0;
			IOSET0=(1<<21);
		}

int main() {

    pll_in();  // Initialize PLL
while (1) {
    PINSEL0 = 0x00000000;  // Set all pins as GPIO
    PINSEL2 = 0x00000000;
		IODIR0 &=~(0<<1);  // Set  pins of Port 0.21 as input
    IODIR0 |= (1 << 21);   // Set P0.21 as output
    IODIR1 |= (1 << 31);   // Set P1.31 as output

    EXTINT = (1 << 0);     // Clear EINT0 flag
    EXTMODE = (0 << 0);    // Level-sensitive mode
    EXTPOLAR = (1 << 0);   // -VE polarity

    VICIntSelect = (0 << 14);        // EINT0 as IRQ
    VICIntEnable = (1 << 14);        // Enable EINT0 interrupt
    VICVectCntl1 = (1 << 5) | 14;    // Enable and assign slot 1 to EINT0
    VICVectAddr1 = (unsigned int)myISR;

    
        IOSET1 = (1 << 31);  // Set P1.31 high
        for (i = 0; i < 50000; i++);  // Delay
        IOCLR1 = (1 << 31);  // Set P1.31 low
        for (i = 0; i < 50000; i++);  // Delay
    }
}



