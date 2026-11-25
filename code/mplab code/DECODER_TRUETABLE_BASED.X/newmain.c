

// PIC16F876A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
void main(void) {
    TRISB=0X07;
    PORTB=0X00;
    TRISC=0X00;
    PORTC=0X00;
    while(1){
        if((RB0==0)&&(RB1==0)&&(RB2==0))
        {
            PORTC=0X01;
        }
        if((RB0==0)&&(RB1==0)&&(RB2==1))
        {
            PORTC=0X02;
        }
        if((RB0==0)&&(RB1==1)&&(RB2==0))
        {
            PORTC=0X04;
        }
        if((RB0==0)&&(RB1==1)&&(RB2==1))
        {
            PORTC=0X08;
        }
        if((RB0==1)&&(RB1==0)&&(RB2==0))
        {
            PORTC=0X10;
        }
        if((RB0==1)&&(RB1==0)&&(RB2==1))
        {
            PORTC=0X20;
        }
        if((RB0==1)&&(RB1==1)&&(RB2==0))
        {
            PORTC=0X40;
        }
        if((RB0==1)&&(RB1==1)&&(RB2==1))
        {
            PORTC=0X80;
        }
    }
    
    return;
}
