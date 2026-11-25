
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
#define _XTAL_FREQ 4000000
#include <string.h>
void next()
{
    TXREG='\r';
    while(!(TRMT));
    TXREG='\n';
    return;
}
void printing(void *ptr ,void n)
{
     for(int i=0;i<n;i++)
    {
      TXREG=(*ptr+i);
    __delay_ms(200);
     while(TRMT==0);
    }
     next();
     return;
}
void reset ()
{
      for(int i=0;;i++)
     {
         while(!RCIF);
         c[i]=RCREG;
         if(c[i]=='\r')
         {
             c[i]='\0';
             break;
         }
         TXREG=c[i];
         while(!(TRMT));
     }
        next();
        int i,j;
        for(i=0 j=0 ; i<=10 j<=10 ;i++ j++)
        {
            ch[i]=c[i];
        }
        printing(p,10);
}
void main(void) {
    char*ptr;
    TRISC=0X80;
    RCSTA=0X90;
    SPBRG=25;
    TXSTA=0X024;
   char R[5]="FAIL";
   char ch[10]="HRITHWIK";
   char pass[20]="ENTER YOUR PASSWORD";
   char p[10]="success";
   char c[10];
     
   while(1){
       printing(pass,20);
     for(int i=0;;i++)
     {
         while(!RCIF);
         c[i]=RCREG;
         if(c[i]=='\r')
         {
             c[i]='\0';
             break;
         }
         TXREG=c[i];
         while(!(TRMT));
     }
        next();
     int var=strcmp(ch,c);
     if(var==0)  
     {
     printing(p,10);
     }
     else{
        printing(R,5);
        reset();
   }

  
}
}
