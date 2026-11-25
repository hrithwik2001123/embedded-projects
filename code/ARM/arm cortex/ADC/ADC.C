#include <lpc17xx.h>
#define PCLK 60000000
#include <stdio.h>
 char arr[15];
 int result,i;


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
 LPC_GPIO0->FIODIR=0X00000000;
	LPC_PINCON->PINSEL1|=(1<<16)|(1<<17);
    uart_in(9600); // Initialize UART
	LPC_ADC->ADCR=0X00210402;
    while (1) {
				LPC_ADC->ADCR|=(1<<24);
			while(!(LPC_ADC->ADGDR&0X80000000));//: A/D Global Data Register (AD0GDR -31 BIT WILL HIGH 80000000 USING This bit is set to 1 when an A/D conversion completes. It is cleared  when this register is read and when the ADCR is written.IMPORTANT THINKS IS THE AD0CR -BURST will set 0 not 1
					result=((LPC_ADC->ADGDR>>4)&0XFFF);//4:15 is ADGDR is done anf 0xfff 
        sprintf(arr,"ADC=%d\r\n",result);
				for(i=0;arr[i]!='\0';i++)
						{
								while(!(LPC_UART0->LSR&(1<<5)));
								LPC_UART0-> THR=arr[i];
						}
    }
		
}
