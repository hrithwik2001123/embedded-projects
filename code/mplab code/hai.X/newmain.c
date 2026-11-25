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
#include <stdio.h>
#include <string.h>

void print(char*data){
    while (*data) {
TXREG=*data++;
while(!TRMT);
__delay_ms(100);
}
}
void main(void) {
    char arr[20];
    //ADC
    TRISA=0X01;
    ADCON0=0X41;
    ADCON1=0X80;
    //UART
    TRISC=0X80;
    TXSTA=0X24;
    RCSTA=0X90;
    SPBRG=25;
        GO=1;
        while(GO==1);
  {
            int RES =(ADRESH<<8)|ADRESL;
            sprintf(arr,"ADC=%d\r\n",RES);
            print(arr);
        }
    }
  


