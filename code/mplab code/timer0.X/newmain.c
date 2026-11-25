
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
#define __XTAL_FREQ 4000000
void delay()
{
    for(int i=0;i<1000;i++)
    {
        while(TMR0IF==0);
        TMR0=5;
        TMR0IF=0;
    }
}
void main(void) {
     TMR0=5;
     TRISB = 0x00;    // Set all PORTB pins as output
    PORTB = 0x00;    // Initialize PORTB to 0
    OPTION_REG=0X01;
    while (1) {
        PORTB = 0xFF;  // Set all PORTB pins high
       delay(); //DELAY FUCTION
        PORTB = 0x00;  // Set all PORTB pins low
        delay(); // Delay for 500 milliseconds
    }
    return;
}
