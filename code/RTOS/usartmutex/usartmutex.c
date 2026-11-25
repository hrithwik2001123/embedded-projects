 #include "includes.h"
 #include <stdio.h>
 #include <string.h>
 # include <util/delay.h>
char CH[14]="HRITHWIK\r\n";
char H[10]="hai\r\n";
char r[10]="bye\r\n";
OS_STK S1[128];
OS_STK S2[128];
OS_STK S3[128];
void uart();
void uart1();
void uart2();
OS_EVENT*data;
void*error;
int main(void) {
    TCCR0 = 0x07;  
    TIMSK = 0x01;
    DDRE= (1<<1);
	UCSR0A=0X00;
	UCSR0B=0X18;
	UCSR0C=0X06;
	UBRR0L=103;
    OSInit();
	data = OSMutexCreate(4,error);
    OSTaskCreate(uart,0XFF,&S1[127],5);
	OSTaskCreate(uart1,0XFF,&S2[127],6);
	OSTaskCreate(uart2,0XFF,&S3[127],7);
	    OSStart();
 return 0;

}

void uart() {
int i;


while(1){
OSMutexPend(data,0,error);
	for(i=0;CH[i]!='\0';i++){
	
	UDR0=CH[i];
 
	while(!(UCSR0A&(1<<6)));
	
    }
	OSMutexPost(data);
	OSTimeDlyHMSM(0,0,1,0);
	
	}
	
	
}
void uart1() {
int i;


while(1){
OSMutexPend(data,0,error);

	for(i=0;H[i]!='\0';i++){ 
	UDR0=H[i];
 
	while(!(UCSR0A&(1<<6)));
	
    
	}
	OSMutexPost(data);
	
OSTimeDlyHMSM(0,0,1,0);}
}
void uart2() {
int i;


while(1){
OSMutexPend(data,0,error);

	for(i=0;r[i]!='\0';i++){ 
	UDR0=r[i];
 
	while(!(UCSR0A&(1<<6)));
	
    
	}
	OSMutexPost(data);
OSTimeDlyHMSM(0,0,1,0);}
}

