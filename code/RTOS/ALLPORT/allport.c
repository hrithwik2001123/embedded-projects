#include "includes.h"

OS_STK S1[128];
OS_STK S2[128];
OS_STK S3[128];
OS_STK S4[128];
OS_STK S5[128];
OS_STK S6[128];
OS_STK S7[128];

void BLINK(void);

int main(void) {
    DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
    PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	PORTF = 0x00;
	PORTG = 0x00;
    TCCR0 = 0x07;  
    TIMSK = 0x01;

    OSInit();
    OSTaskCreate(BLINK,0XFF,&S1[127],4);
	OSTaskCreate(BLINK,0XFF,&S2[127],5);
	OSTaskCreate(BLINK,0XFF,&S3[127],6);
	OSTaskCreate(BLINK,0XFF,&S4[127],7);
	OSTaskCreate(BLINK,0XFF,&S5[127],8);
	OSTaskCreate(BLINK,0XFF,&S6[127],9);
	OSTaskCreate(BLINK,0XFF,&S7[127],10);
    OSStart();

}

void BLINK() {
    while (1) {
        PORTA = ~PORTA;
        OSTimeDlyHMSM(0, 0, 1, 0);
		PORTB = ~PORTB;
        OSTimeDlyHMSM(0, 0, 1, 0);
		PORTC = ~PORTC;
        OSTimeDlyHMSM(0, 0, 1, 0);
		PORTD = ~PORTD;
        OSTimeDlyHMSM(0, 0, 1, 0);
		PORTE = ~PORTE;
        OSTimeDlyHMSM(0, 0, 1, 0);
		PORTF = ~PORTF;
        OSTimeDlyHMSM(0, 0, 1, 0);
		PORTG = ~PORTG;
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
