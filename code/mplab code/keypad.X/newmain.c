#pragma config FOSC = XT       // Oscillator Selection
#pragma config WDTE = OFF      // Watchdog Timer Enable
#pragma config PWRTE = OFF     // Power-up Timer Enable
#pragma config BOREN = OFF     // Brown-out Reset Enable
#pragma config LVP = OFF       // Low Voltage Programming Disable
#pragma config CPD = OFF       // Data EEPROM Code Protection
#pragma config WRT = OFF       // Flash Program Memory Write Protection
#pragma config CP = OFF        // Flash Program Memory Code Protection

#include <xc.h>

#define _XTAL_FREQ 4000000     // Define system clock frequency

// LCD control pins
#define RS RC0
#define RW RC1
#define E  RC2

// Function to send a command to the LCD
void command(char b) {
    PORTC = (b & 0xF0); // Send high nibble to PORTC (assume LCD is connected to PORTC)
    RS = 0; RW = 0; E = 1;
    __delay_ms(2);
    E = 0;

    PORTC = (b << 4); // Send low nibble
    RS = 0; RW = 0; E = 1;
    __delay_ms(2);
    E = 0;
}

// Function to initialize the LCD
void lcdinit() {
    __delay_ms(20); // Power-on delay
    command(0x02); // Initialize in 4-bit mode
    command(0x28); // Function set: 4-bit, 2-line, 5x7 font
    command(0x0C); // Display ON, Cursor OFF
    command(0x06); // Entry mode: Increment, no shift
    command(0x01); // Clear display
}

// Function to send data to the LCD
void data(char b) {
    PORTC = (b & 0xF0); // High nibble
    RS = 1; RW = 0; E = 1;
    __delay_ms(2);
    E = 0;

    PORTC = (b << 4); // Low nibble
    RS = 1; RW = 0; E = 1;
    __delay_ms(2);
    E = 0;
}

// Function to reset the keypad (set rows to HIGH)
void resetKeypad() {
    PORTB = 0x0F; // Rows HIGH, Columns LOW
}

// Function to scan the keypad and return the pressed key
char keypad() {
    char keys[4][4] = { // Keypad mapping
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'C', '0', '=', '+'}
    };

    while (1) {
        for (int row = 0; row < 4; row++) {
            resetKeypad(); // Reset all rows to HIGH
            PORTB &=~(1 << row); // Set current row LOW

            __delay_ms(20); // Debounce delay

            // Check columns for a LOW signal
            if (RB4 == 0) { __delay_ms(200); return keys[row][0]; }
            if (RB5 == 0) { __delay_ms(200); return keys[row][1]; }
            if (RB6 == 0) { __delay_ms(200); return keys[row][2]; }
            if (RB7 == 0) { __delay_ms(200); return keys[row][3]; }
        }
    }
}

// Main function
void main(void) {
    // Configure PORTC for LCD, PORTB for keypad
    TRISC = 0x00; // PORTC as output (control + data for LCD)
    TRISB = 0xF0; // Upper nibble (RB4?RB7) as input, lower nibble (RB0?RB3) as output

    PORTC = 0x00; // Initialize PORTC
    PORTB = 0x00; // Initialize PORTB

    // Initialize LCD
    lcdinit();

    while (1) {
        char key = keypad(); // Read key from keypad
        data(key);           // Display the key on the LCD
    }
}
