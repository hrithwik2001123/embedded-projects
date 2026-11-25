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
#define RS RB0
#define RW RB1
#define E  RB2

// Function to send a command to the LCD
void command(char b) {
    PORTC = b;  // Send command to PORTC
    RS = 0;     // RS = 0 for command
    RW = 0;     // RW = 0 for write
    E = 1;      // Generate a high-to-low pulse on E
    __delay_ms(2); // Short delay
    E = 0;
     PORTC = b<<4;  // Send command to PORTC
    RS = 0;     // RS = 0 for command
    RW = 0;     // RW = 0 for write
    E = 1;      // Generate a high-to-low pulse on E
    __delay_ms(2); // Short delay
    E = 0;
}

// Function to initialize the LCD
void lcdinit() {
    command(0x02); // Initialize in 4-bit mode
    command(0x28); // Function set: 8-bit, 2 lines, 5x7 font
    command(0x0C); // Display ON, Cursor OFF
    command(0x01); // Clear display
    command(0x80); // Set cursor to the beginning of the first line
}

// Function to send data to the LCD
void data(char b) {
    PORTC = b;  // Send data to PORTC
    RS = 1;     // RS = 1 for data
    RW = 0;     // RW = 0 for write
    E = 1;      // Generate a high-to-low pulse on E
    __delay_ms(2); // Short delay
    E = 0;
    PORTC = b<<4;  // Send data to PORTC
    RS = 1;     // RS = 1 for data
    RW = 0;     // RW = 0 for write
    E = 1;      // Generate a high-to-low pulse on E
    __delay_ms(2); // Short delay
    E = 0;
}

// Function to print a string on the LCD
/*void printString( char *str) {
    while (*str) {      // Loop until the null character is reached
        data(*str++);   // Send each character to the LCD
    }
}*/

// Main function
void main(void) {
    // Configure PORTC and PORTB as output
    TRISC = 0x00; // Set PORTC as output (for data)
    TRISB = 0x00; // Set PORTB as output (for control)
    // Initialize PORT values to 0
    PORTC = 0x00; 
    PORTB = 0x00;
    
    // Initialize LCD
    lcdinit();
    // Print "Hello World" on the LCD
    char s[6] ="Hello";
    for(int i = 0;s[i]!='\0';i++){
        data(s[i]);
    }
    while (1); // Infinite loop to keep the program running
}
