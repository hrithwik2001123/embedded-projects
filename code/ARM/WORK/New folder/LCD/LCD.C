#include <lpc214x.h>
# define PCLK 60000000
#define RS (1 << 16) // P0.16
#define RW (1 << 17) // P0.17
#define E  (1 << 18) // P0.18
int i;
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

void command(char b) {
    IOPIN0 =(IOPIN0&0X0001FF00) ;  // Send command to PORTC
   // RS = 0;     // RS = 0 for command
    //RW = 0;     // RW = 0 for write
	  IOCLR0=RS|RW;
	   IOSET0 = E;             // Enable high
//    E = 1;      // Generate a high-to-low pulse on E
   for(i=0;i<1000;i++); // Short delay
    IOCLR0 = E;
}
void lcdinit() {
    command(0x02); // Initialize in 4-bit mode
    command(0x28); // Function set: 8-bit, 2 lines, 5x7 font
    command(0x0C); // Display ON, Cursor OFF
    command(0x01); // Clear display
    command(0x80); // Set cursor to the beginning of the first line
}
void data(char b) {
    IOPIN0 =(IOPIN0&0X0001FF00);  
    //RW = 0;     // RW = 0 for write
   //E = 1;      // Generate a high-to-low pulse on E
	   IOSET0=RS|E;// HIGH 
	   IOCLR0=RW;//LOW
    for( i=0;i<1000;i++); // Short delay
    //E = 0;
	 IOCLR0 = E;//ENABLE IN LOW
}
void printString( char *str) {
    while (*str) {      // Loop until the null character is reached
        data(*str++);   // Send each character to the LCD
    }
}
int main()
{
	
		PINSEL0 = 0x00000000; // Set P0.0 to P0.15 as GPIO
    IODIR0 = 0x0001FF00;  // Set P0.8 to P0.15 as output for LCD
		lcdinit();            // Initialize LCD
    printString("Hello ARM"); // Print string on LCD
	  while(1);
}
