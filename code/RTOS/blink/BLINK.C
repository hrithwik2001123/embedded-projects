
 #include "includes.h"

OS_STK S1[128];

void BLINK(void);

int main(void) {
    DDRA = 0xFF;
    PORTA = 0x00;
    TCCR0 = 0x07;  
    TIMSK = 0x01;

    OSInit();
    OSTaskCreate(BLINK,0XFF,&S1[127],4);
    OSStart();

    return 0;
}

void BLINK() {
    while (1) {
        PORTA = ~PORTA;
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}
