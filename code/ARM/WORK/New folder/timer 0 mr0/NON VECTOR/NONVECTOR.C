#include <lpc214x.h>
# define PCLK 60000000
char CH;
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
uart_in(unsigned int baudrate)
	 {
		 unsigned int DL;
		 PINSEL0=0X05;
		 U0LCR=0X83;
		 DL=(PCLK/16)/baudrate;
		 U0DLM=DL>>8;
		 U0DLL=DL&0XFF;
		 U0LCR=0X03;
		 U0IER=(1<<0);
	 }
void myISR(void)__irq
		
			{
			if(U0IIR&0X04)
				{
					while(!(U0LSR&(1<<0)));
					//CH=U0RBR;
					U0THR=U0RBR;
				
						if(U0RBR=='A')
						{
							IOSET0=(1<<5);
						}
						else if(U0RBR=='B')
						{
							IOSET0=(1<<8);
						}
						VICDefVectAddr=0;
			
		  }
		
			
		}
		

int main() {
    pll_in(); 	// Initialize PLL
     PINSEL2 = 0x00000000; // Set all pins as GPIO
	   PINSEL0 = 0x00000000; // Set all pins as GPIO
     IODIR0 = 0xFFFFFFFF;  // Set all pins of Port 0 as output
     IODIR1 = 0xFFFFFFFF;  // Set all pins of Port 0 as output
		VICIntSelect=(0<<6);
		VICIntEnable=(1<<6);
	  VICVectCntl1=(1<<5)|6;
	  VICVectAddr1=(unsigned)myISR;
   		uart_in(9600);
    while (1)
		{
			IOSET1=0x80000000;
		}
}
