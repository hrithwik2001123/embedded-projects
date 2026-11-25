 #include "includes.h"
 #include <stdio.h>
OS_STK S1[128];
OS_STK S2[128];
    char arr[20];   
	int i,RES;
void adc(void);
void uart(void);

int main(void) {
   
	
	    // ADC initialization
    DDRF= 0X00;    
    ADCSRA = 0x87;  
    ADMUX = 0x40;
	TCCR0 = 0x07;  
    TIMSK = 0x01;
	//uart
    DDRE= 0x02;
	UCSR0A=0X00;
	UCSR0B=0X18;
	UCSR0C=0X06;
	UBRR0L=103;
    OSInit();
    OSTaskCreate(adc,0XFF,&S1[127],4);
	OSTaskCreate(uart,0XFF,&S2[127],5);
    OSStart();
return 0;

}   
   void adc(){
while(1){
	   
        ADCSRA |=(1<<6);  
        while (!(ADCSRA & (1<<4)));     
         int RES = ADCL|(ADCH<<8) ;        
        sprintf(arr, "ADC1=%d\r\n", RES);
	    OSTimeDlyHMSM(0, 0, 1, 0);

		
} 
}
void uart () {
while(1){
    for( i=0;arr[i]!='\0';i++) {
   UDR0=arr[i]; 
   
while(!(UCSR0A&(1<<5)));  
  }
   OSTimeDlyHMSM(0, 0, 1, 0);

   
}
}
