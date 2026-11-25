/**************************************************************************
Target		:ATMega128
CPU Clock	:16MHZ
Compiler	:avr gcc
Description	:This is a program for industrial automation using rfid and lm 35.
Author		:SREEKANTH R V <rvsreekanth@gmail.com>

**************************************************************************/

//////////////////  INCLUDES HEADER FILES  ////////////////////////////////
#include<includes.h>	//for RTOS
#include<avr/io.h>
#include<util/delay.h>
#include "LCD_mega128.h"




//////////////////////////////////////////////////////////////////////////
//////////////////////Global variables////////////////////////////////////
int i=0;

///////////////////////////////////////////////////////////////////////////


//////////////////  PROTOTYPES  //////////////////////////////////////////
void task1();
void task2();

//////////////////////////////////////////////////////////////////////////

//////////////////  #DEFINE AND GLOBAL VARIABLES  ////////////////////////
#if defined(__AVR_AT90S2313__) || defined(__AVR_AT90S2333__) || defined(__AVR_AT90S4433__) || \
        defined(__AVR_AT90S4434__) || defined(__AVR_AT90S8535__) || defined(___AVR_ATmega8535__)
# error "Your MCU probably does not have enough SRAM to run this program"
#elif defined(__AVR_AT90S4414__) 
# error "Your MCU probably does not have enough program memory to run this program"
#elif defined(__AVR_AT90S8515__) || \
       defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__) || defined(__AVR_ATmega163__) || \
       defined(___AVR_ATmega8515__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
       defined(__AVR_ATmega8__)
#   define TCCR0VAL delay(_BV(CS02) | _BV(CS00))
#elif defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega103__)
#   define TCCR0VAL (_BV(CS02) | _BV(CS01) | _BV(CS00))
#else
#  error "Don't know what kind of MCU you are compiling for"
#endif

#define MYTASK_STACK 512


OS_STK MyTaskStack1[MYTASK_STACK];
OS_STK MyTaskStack2[MYTASK_STACK];



//////////////////////////////////////////////////////////////////////////

////////////////////////////Defnitions///////////////////////////////////

#define dooropen	((PORTC & (0xfe))|0x02)
#define doorclose	((PORTC & (0xfd))|0x01)
#define dataarrived	((PORTC & (0x7f))|0x40)
#define showid		((PORTC & (0xbf))|0x80)
#define invalidid	((PORTC & (0xfb))|0x04)
#define temphigh	((PORTC & (0xef))|0x2c)
#define tempnormal	((PORTC & (0xf7))|0x34)
#define templow		((PORTC & (0xfb))|0x38)
#define dopenrelay      ((PORTB | (0x40))&0x40)
#define dcloserelay	(PORTB & (0xbf))
////////////////////////////ISR//////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////

int main(void)
{
	OSInit();

     //TIMSK|=(1<<TOIE0);
	OS_ENTER_CRITICAL();
		TCCR0=0x07;//TCCR0VAL;                              /* Set TIMER0 prescaler to CLK/1024                 */
		TIMSK=_BV(TOIE0);                                   /* Enable TIMER0 overflow interrupt                 */
		TCNT0=(256-((CPU_CLOCK_HZ/OS_TICKS_PER_SEC)/1024));   /* Set the counter initial value                    */
	OS_EXIT_CRITICAL();
    
     DDRG=0xff;
 PORTG=0x00;
 UBRR1L=0x67;
 UBRR1H=0x00;
 UCSR1B=0x18;
 DDRC=0xff;
 PORTC=0xff;
 PORTC=doorclose;
 PORTC=showid;
 DDRB=0xff;
 PORTB=0x00;
 sei();
 while((UCSR1A&0x20)!=0X20);
					UDR1='A';
					while(1);
 //lcd_init();
     OSTaskCreate(task1,(void *)0, &MyTaskStack1[ MYTASK_STACK - 1 ], 1 ); 
     OSTaskCreate(task2,(void *)0, &MyTaskStack2[ MYTASK_STACK - 1 ], 2 );
     
     OSStart();
     return(0);
}

void task1()/*This task configures the uart on atmega 128 and dals with the validation of RFID*/
{
 

// uart_rec_sem=OSSemCreate(0);
 

 while(1)
{


  
//lcd_putchar('A');
 
//OSTimeDlyHMSM(0,0,2,0);



}
}
 void task2()/*This task controls the tempeture sensor*/

{
       char i,j;
       
      
       while(1)

      {
		while((UCSR1A&0x20)!=0X20);
					UDR1='B';
		OSTimeDlyHMSM(0,0,1,0);
      }
}

////////////////////////function///////////////////////////////////////////
void delay(int count)
{
 int i,j;
 for(i=0;i<count;i++)
 for(j=0;j<0xffff;j++);
}
/////////////////////////////////////////////////////////////////////////////




