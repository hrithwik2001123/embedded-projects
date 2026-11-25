#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000  // 4 MHz crystal frequency
#define DUTY_CYCLE_MAX 255  // Maximum duty cycle (8-bit PWM)

volatile union S31 {
    unsigned char dutyCycle;  // PWM duty cycle value
};

// Configuration bits
#pragma config FOSC = HS        // High-speed oscillator
#pragma config WDTE = OFF       // Watchdog timer disabled
#pragma config PWRTE = OFF      // Power-up timer disabled
#pragma config BOREN = OFF      // Brown-out reset disabled
#pragma config LVP = OFF        // Low-voltage programming disabled
#pragma config CPD = OFF        // Data EEPROM memory code protection off
#pragma config WRT = OFF        // Flash memory write protection off
#pragma config CP = OFF         // Code protection off

// Declare a volatile union to hold the PWM duty cycle
volatile union S31 myUnion;

void main(void) {
    TRISB = 0x00;  // Set PORTB as output (for PWM control)
    TRISCbits.TRISC2 = 0;  // Set RC2 (CCP1 pin) as output for PWM
    T1CON = 0x21;  // Set Timer1 for 8-bit prescaler (1:4)
    
    // Setup PWM mode on CCP1 (pin RC2)
    CCP1CON = 0x0C;  // PWM mode, P1A and P1B enabled

    // Initialize duty cycle to 0
    myUnion.dutyCycle = 0;
    
    while (1) {
        // Check for user input ('a' to increase, 'b' to decrease)
        if (PIR1bits.RC1IF) {  // Check if data is available in UART
            char input = RCREG;  // Read the received character
            
            if (input == 'a') {  // Increase brightness (PWM duty cycle)
                if (myUnion.dutyCycle < DUTY_CYCLE_MAX) {
                    myUnion.dutyCycle++;
                }
            }
            else if (input == 'b') {  // Decrease brightness (PWM duty cycle)
                if (myUnion.dutyCycle > 0) {
                    myUnion.dutyCycle--;
                }
            }
            
            // Update the PWM duty cycle register
            CCPR1L = myUnion.dutyCycle;  // Update the 8-bit duty cycle for PWM
        }
    }
}
