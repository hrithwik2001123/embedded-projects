#pragma config FOSC = XT       
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF     
#pragma config BOREN = OFF     
#pragma config LVP = OFF       
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF 

#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000  // Define system clock frequency (4 MHz)

char arr[10];  // Array to store formatted time string

// Function to initiate I2C start condition
void start()
{
    SEN = 1;  // Generate Start condition
    while(SSPIF == 0);  // Wait for start condition to complete
    SSPIF = 0;  // Clear interrupt flag
}

// Function to initiate I2C stop condition
void stop()
{
    PEN = 1;  // Generate Stop condition
    while(SSPIF == 0);  // Wait for stop condition to complete
    SSPIF = 0;  // Clear interrupt flag
}

// Function to initiate I2C restart condition
void restart()
{
    RSEN = 1;  // Generate Restart condition
    while(SSPIF == 0);  // Wait for restart condition to complete
    SSPIF = 0;  // Clear interrupt flag
}

// Function to send ACK signal (acknowledge)
void ack()
{
    ACKDT = 0;  // ACK (0 = ACK, 1 = NACK)
    ACKEN = 1;  // Enable ACK
    while(SSPIF == 0);  // Wait for ACK to complete
    SSPIF = 0;  // Clear interrupt flag
}

// Function to send NACK signal (no acknowledge)
void nack()
{
    ACKDT = 1;  // NACK (0 = ACK, 1 = NACK)
    ACKEN = 1;  // Enable NACK
    while(SSPIF == 0);  // Wait for NACK to complete
    SSPIF = 0;  // Clear interrupt flag
}

// Function to send a byte via I2C and return ACK status
int send(char b)
{
    SSPBUF = b;  // Load byte to be sent to SSPBUF (I2C data register)
    while(SSPIF == 0);  // Wait for byte to be transmitted
    SSPIF = 0;  // Clear interrupt flag
    return(ACKSTAT);  // Return acknowledgment status (1 = ACK received, 0 = NACK received)
}

// Function to read a byte via I2C
char read()
{
    RCEN = 1;  // Enable receive mode
    while(SSPIF == 0);  // Wait for data to be received
    SSPIF = 0;  // Clear interrupt flag
    return SSPBUF;  // Return received data
}

// Function to transmit a string via USART (for displaying time)
void txt(char* ptr)
{
    for (int i = 0; *(ptr + i) != '\0'; i++)
    {
        TXREG = *(ptr + i);  // Load each character into TXREG (USART transmit register)
        while (TRMT == 0);  // Wait for the transmit buffer to be empty
    }
}

// Main function
void main(void) 
{
    // Initialize UART (USART) settings for serial communication
    TRISC = 0x98;  // 1001 1000 (RC3 & RC4 as input, RC6 as output, RC7 as input)
    TXSTA = 0x24;  // Enable transmitter, asynchronous mode
    RCSTA = 0x90;  // Enable receiver, continuous receive
    SPBRG = 25;  // Baud rate generator value for 9600 baud (4 MHz clock)
    
    // Initialize I2C settings (Master mode)
    SSPADD = 9;  // I2C clock speed (100kHz)
    SSPSTAT = 0x80;  // Disable slew rate control (standard mode)
    SSPCON = 0x28;  // Enable I2C Master mode

    // **Write Initial Time to DS1307 RTC**
    start();  // Start I2C communication
    while (send(0xD0) == 1)  // Send RTC address (write mode), retry if NACK received
    {
        start();
    }
    
    send(0x00);  // Select register 0 (Seconds)
    send(0x00);  // Set seconds to 0x00 (00 seconds)
    send(0x10);  // Set minutes to 0x10 (10 minutes)
    send(0x12);  // Set hours to 0x12 (12 hours)
    stop();  // Stop I2C communication

    // **Infinite loop to continuously read RTC time and display**
    while (1)
    {
        start();  // Start I2C communication
        while (send(0xD0) == 1)  // Send RTC address (write mode)
        {
            start();
        }
        
        send(0x00);  // Select register 0 (Seconds)
        restart();  // Send restart condition
        
        send(0xD1);  // RTC address (read mode)
        int sec = read();  // Read seconds
        ack();  // Send ACK
        
        int min = read();  // Read minutes
        ack();  // Send ACK
        
        int hr = read();  // Read hours
        nack();  // Send NACK (stop reading)
        
        stop();  // Stop I2C communication

        // Format time as "HH:MM:SS" and store in array
        sprintf(arr, "%X:%X:%X\r\n", hr, min, sec);
        
        // Send formatted time via USART
        txt(arr);
        
        __delay_ms(1000);  // Wait for 1 second before reading time again
    }
}
