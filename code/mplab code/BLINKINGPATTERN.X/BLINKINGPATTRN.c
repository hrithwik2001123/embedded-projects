/*
 * File:   BLINKINGPATTRN.c
 * Author: user
 *
 * Created on 2 November, 2024, 10:09 AM
 */


// PIC16F876A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000
#include <xc.h>
void main(void) {
    int i,j;
    TRISB=0X00;
    TRISC=0X00;
    PORTB=0X00;
    PORTC=0X00;
    while(1)
    {
        for(i=8,j=0;i>0&&j<9;i--,j++)
        {
            PORTB=0X01<<i;
            PORTC=0X01<<j;
            __delay_ms(500);
        }
    }
    return;
}
