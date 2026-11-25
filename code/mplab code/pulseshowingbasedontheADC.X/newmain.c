#include <xc.h>
#include<stdio.h>
#define _XTAL_FREQ 4000000

#pragma config FOSC = XT        // XT Oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = OFF      // Power-up Timer disabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low-voltage Programming disabled
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection disabled
#pragma config WRT = OFF        // Flash Program Write Protection disabled
#pragma config CP = OFF         // Code Protection disabled

void main(void) {
    /*TRISA=0X01;// RA0 IS INPUT 
    ADCON1=0X08;//CCP1 IS OUTPUT
    TRISC=0X00;//PORTC IS SET AS  OUTPUT
    PORTC=0X00; //PORTC IS CLEAR
    CCP1CON=0X2C;//25% DUTYCYCLE
    CCP1CON = 0x0C; // Configure CCP1 as PWM
       // ADC configuration
    ADCON1 = 0x08;  // Configure AN0 (RA0) as analog, others as digital
    ADCON0 = 0x41;  // ADC enabled, select AN0, right justified
    CCPR1L=0X0F;
    while(1)
    {
        ADCON0=0X49;
         T2CON=0X04;
          PR2=62;
        GO=1;
        while(GO==1);
        int RES=(ADRESH<<8)|ADRESL;
        CCPR1L=RES;
    }*/
    TRISA = 0x01;   // RA0 is input
    ADCON1 = 0x08;  // Configure AN0 (RA0) as analog, others as digital
    TRISC = 0x00;   // PORTC is output
    PORTC = 0x00;   // Clear PORTC
    CCP1CON = 0x0C; // Configure CCP1 as PWM
    T2CON = 0x04;   // Timer2 ON, prescaler 1:1
    PR2 = 62;       // Set PWM period (adjust if needed)

    while(1) {
        ADCON0 = 0x41; // Enable ADC, select AN0
        __delay_us(10); // Acquisition time
        GO = 1;         // Start ADC conversion
        while(GO);      // Wait for conversion to complete

        unsigned int RES = (ADRESH << 8) | ADRESL; // Combine ADC result
        CCPR1L = RES >> 2; // Scale ADC result to fit 8-bit CCPR1L
    }
}
