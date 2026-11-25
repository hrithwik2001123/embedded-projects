

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
#define __XTAL_FREQ 4000000
void start{
    SEN=1;
    while(SSPIF==0);
    SPPIF=0;
    
}
void stop{
    PEN=1;
    while(SSPIF==0);
    SPPIF=0;
    
}
void restart{
    RSEN=1;
    while(SSPIF==0);
    SPPIF=0;
    
}
void print(const char *s) {
        TXREG = *s++;
        while (!TRMT);
    while (!TRMT);
    next();
}
void main(void) {
    
    return;
}
