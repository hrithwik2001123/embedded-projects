/**************************************************************************
Target		:ATMega128
CPU Clock	:16MHZ
Compiler	:avr gcc
Description	:This is a program for industrial automation using rfid and lm 35.
Author		:SARIN MS <sarinms1982@gmail.com>

**************************************************************************/

//////////////////  INCLUDES HEADER FILES  ////////////////////////////////
#include<includes.h>	//for RTOS
#include<avr/io.h>
#include<util/delay.h>




//////////////////////////////////////////////////////////////////////////
//////////////////////Global variables////////////////////////////////////
int i=0;
char RFID=0;
char buffer[15];
void delay(int);
int buffer_count=0;
OS_EVENT *uart_rec_sem;
char err;
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
ISR(USART1_RX_vect)
{ 
  cli();
  buffer[buffer_count]=UDR1;
  buffer_count++;
  if(buffer_count>=15)
  {
   PORTC=dataarrived;
   buffer_count=0;
   OSSemPost(uart_rec_sem);
    
   
  }
 if(RFID==0)
 {
  TCNT1L=0x00;
  TCNT1H=0x00;
  TCCR1B=0x04;
  TIMSK=0x04;
  RFID=1;
 }
  
  sei();
}

ISR(TIMER1_OVF_vect)
{
 buffer_count=0;
 TCCR1B=0x00;
 RFID=0;
}
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
     
     
     OSTaskCreate(task1,(void *)0, &MyTaskStack1[ MYTASK_STACK - 1 ], 1 ); 
     OSTaskCreate(task2,(void *)0, &MyTaskStack2[ MYTASK_STACK - 1 ], 2 );
     
     OSStart();
     return(0);
}

void task1()/*This task configures the uart on atmega 128 and dals with the validation of RFID*/
{
 
 char c[]={0x03,0x31,0x43,0x30,0x30,0x46,0x46,0x44,0x31,0x35,0x41,0x36,0x38,0x0A,0x0D};
 int validity=0;
 uart_rec_sem=OSSemCreate(0);
 DDRG=0xff;
 PORTG=0x00;
 UBRR1L=0x67;
 UBRR1H=0x00;
 UCSR1B=0x98;
 DDRC=0xff;
 PORTC=0xff;
 PORTC=doorclose;
 PORTC=showid;
 DDRB=0xff;
 PORTB=0x00;
 sei();
 while(1)
{
 
 
 //while(RFID!=1);
 OSSemPend(uart_rec_sem,0,&err);
 //delay(120);
 for(i=0;i<14;i++)
 {
  if (buffer[i]==c[i])
  validity++; 
  if(validity>=13) 
  {
  //PORTC=0x00;
  validity=0;  
  PORTC=dooropen;
  PORTB=dopenrelay;
  delay(100);
  PORTC=doorclose;
  PORTC=showid;
  PORTB=dcloserelay;
   /*make the relay beat at this interval*/
  }
}
  if(validity>=1)
  {
   //PORTC=invalidid;
   validity=0;
  }
 // UDR1=buffer[i];
  //while(!(UCSR1A&0x40));
  //buffer[i]='0';
  //UCSR1A=0x40;
 


}
}
 void task2()/*This task controls the tempeture sensor*/
{

       char i,j;
       ADMUX=0Xc1;      /*  Selected the channel 1, right adjusted, external Aref is selected  */
       ADCSRA=0XE7;     /*  A/D conversion enabled,Conversion started, free running enabled,
                           interrupt disabled in ADCSRA reg.) , pre-scaler selected       */ 

      
       while(1)

      {

        while((ADCSRA & (1<<ADIF))==0);    /* Checking whether conversion is finished or not  */ 
       {
          i=ADCL;                             /* Moving the 8 bit result to portc from ADCL reg. */
          j=ADCH;    
          
   
          if(i<=0x90)
          PORTC=templow;

        else if((i>=0x92)&&(i<=0xb0))
         PORTC=tempnormal;

         else if(i>0xb5)
        PORTC=temphigh;

     

       }
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




