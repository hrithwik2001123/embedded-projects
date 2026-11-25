
#pragma config FOSC = XT       
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF     
#pragma config BOREN = OFF     
#pragma config LVP = OFF       
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF 

#include <xc.h>
#include<stdio.h>
#include<string.h>
#define _XTAL_FREQ 4000000
#define RS RB0
#define RW RB1
#define E  RB2

void command(char b)
{
      PORTC=b;
    RS=0;
    RW=0;
    E=1;
     __delay_(200);
    E=0;
}
void lcdinit()
{
    command(0x02);
    command(0x38);
    command(0x0c);
    command(0x01);
    command(0x80);
}
void data( char b)
{
    PORTC=b;
    RS=1;
    RW=0;
    E=1;
    __delay_ms(200);
    E=0;
   
}
void main(void) {
    TRISC=0X00;
    TRISB=0X00;
    char ch='A';
    lcdinit();
    data(ch);
}