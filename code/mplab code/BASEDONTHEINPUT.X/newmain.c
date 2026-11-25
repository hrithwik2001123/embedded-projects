
#pragma config FOSC = XT       
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF     
#pragma config BOREN = OFF     
#pragma config LVP = OFF       
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF 

#include <xc.h>

#define __XTAL_FREQ 4000000

void main(void) {
   
    TRISC = 0x80; 
    TXSTA = 0x24;  
    RCSTA = 0x90; 
    SPBRG = 25;    
    CCP1CON = 0x2C;  
    CCPR1L = 0x0F;   
    char CH;        

    while (1) {
          PR2 = 62;       
    T2CON = 0x05;    

        while (!RCIF); 
        CH = RCREG;    
        
        TXREG = CH;  
        while (!TRMT);  

        
        if (CH == 'A') {
            CCPR1L++;
        } else if (CH == 'B') {
            CCPR1L--;  
        }
    }
}
