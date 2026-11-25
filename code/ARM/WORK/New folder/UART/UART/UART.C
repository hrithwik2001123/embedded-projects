#include<lpc214x.h>
#define PCLK 60000000
			int i;
			char ch;
void PLL_IN()
	 {
		 PLL0CON=0X01;
		 PLL0CFG=0X24;
		 PLL0FEED=0XAA;
		 PLL0FEED=0X55;
  while(!(PLL0STAT&1<<10));
		 PLL0CON=0X03;
		 PLL0FEED=0XAA;
		 PLL0FEED=0X55;
		 VPBDIV=0X01;
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
	 }
int main()
		 {
			 PLL_IN();
			 uart_in(9600);
			 while(1)
			 {
	while(!(U0LSR&(1<<0)));
			 U0THR=U0RBR;
			 }
			 
		 }
			 
				
