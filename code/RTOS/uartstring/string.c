 #include "includes.h"
 #include <stdio.h>
 #include <string.h>
char CH[14]="HRITHWIK\r\n";
char H[10]="hai\r\n";
OS_STK S1[128];
OS_STK S2[128];
void uart();
void uart1();
OS_EVENT*data;
OS_EVENT*error;
int main(void) {
    TCCR0 = 0x07;  
    TIMSK = 0x01;
    DDRE= (1<<1);
	UCSR0A=0X00;
	UCSR0B=0X18;
	UCSR0C=0X06;
	UBRR0L=103;
    OSInit();
	data = OSSemCreate(1);
    OSTaskCreate(uart,0XFF,&S1[127],4);
	OSTaskCreate(uart1,0XFF,&S2[127],5);
	
	    OSStart();
 return 0;

}

void uart() {
int i;


while(1){
OSSemPend(data,0,error);
	for(i=0;CH[i]!='\0';i++){
	
	UDR0=CH[i];
OSTimeDly(50); 
	while(!(UCSR0A&(1<<6)));
	
    }
	OSSemPost(data);
	
	}
	
	
}
void uart1() {
int i;


while(1){
OSSemPend(data,0,error);

	for(i=0;H[i]!='\0';i++){ 
	UDR0=H[i];
  OSTimeDly(30);
	while(!(UCSR0A&(1<<6)));
	
    
	}
	OSSemPost(data);
}
}
