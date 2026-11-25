 #include "includes.h"
char CH;
OS_STK S1[128];
OS_STK S2[128];
void uart(void);

int main(void) {
    DDRA = 0xFF;
    PORTA = 0x00;
    TCCR0 = 0x07;  
    TIMSK = 0x01;
    DDRE= (1<<1);
	UCSR0A=0X00;
	UCSR0B=0X18;
	UCSR0C=0X06;
	UBRR0L=103;
    OSInit();
    OSTaskCreate(uart,0XFF,&S1[127],4);
    OSStart();


}

void uart() {
    while (1) {
	while(!(UCSR0A&(1<<7)));
	UDR0=UDR0;
	while(!(UCSR0A&(1<<6)));
	if(UDR0=='h'){
        PORTA = ~PORTA;
        OSTimeDlyHMSM(0, 0, 1, 0);
		}
    }
}

