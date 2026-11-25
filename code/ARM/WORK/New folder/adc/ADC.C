#include<lpc214x.h>
#define PCLK 60000000
#include <stdio.h>
 char arr[15];
 int result,i;
void pll ()
		{
				PLL0CON=0X01;
				PLL0CFG=0X24;
				PLL0FEED=0XAA;
				PLL0FEED=0X55;
		while(!(PLL0STAT&(1<<10)));
				PLL0CON=0X03;
				PLL0FEED=0XAA;
				PLL0FEED=0X55;
				VPBDIV=0X01;
		}
uart_init(unsigned int baudrate)
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
				pll();
					IODIR0=0XFFFFFFF0;
					AD0CR=0X00210D80;
					uart_init(9600);
	    while(1)
			{
					AD0CR|=(1<<24);
					while(!(AD0GDR&0X80000000));
					result=((AD0GDR>>6)&0X3FF);
					sprintf(arr,"ADC=%d\r\n",result);
				for(i=0;arr[i]!='\0';i++)
						{
								while(!(U0LSR&(1<<5)));
								U0THR=arr[i];
						}
			}
		}
		