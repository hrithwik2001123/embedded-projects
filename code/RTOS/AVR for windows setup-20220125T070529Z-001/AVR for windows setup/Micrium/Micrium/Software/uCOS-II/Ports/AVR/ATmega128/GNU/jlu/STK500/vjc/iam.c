


//////////////////  INCLUDES HEADER FILES  ////////////////////////////////
#include<includes.h>	//for RTOS
#include<avr/io.h>
#include<util/delay.h>

#include<LCD_mega128.h>


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
void task3();
void rec();

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
OS_STK MyTaskStack3[MYTASK_STACK];


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
     UBRR1L=0x67;
	UBRR1H=0x00;
	UCSR1B=0x18;
	UBRR0L=0x67;
	UBRR0H=0x00;
	UCSR0B=0x18;
	DDRC=0xff;
	sei();
     lcd_init();
	 //lcd_string("BLACK BOX");
    // OSTaskCreate(task1,(void *)0, &MyTaskStack1[ MYTASK_STACK - 1 ], 1 ); 
     OSTaskCreate(task2,(void *)0, &MyTaskStack2[ MYTASK_STACK - 1 ], 2 );
    // OSTaskCreate(task3,(void *)0, &MyTaskStack3[ MYTASK_STACK - 1 ], 3 );
     OSStart();
     return(0);
}

void task1()/*This task configures the uart on atmega 128 and dals with the validation of RFID*/
{
 
 
 
 
 while(1)
{
 
 lcd_cmd(0x01);
 
 
  //while((UCSR1A&0x20)!=0X20);
					//UDR1='A';

  
 


OSTimeDlyHMSM(0,1,0,0);
}
}
 void task2()/*This task controls the tempeture sensor*/
{

       char i,j,k=3,l;
       

      DDRA|=0x08;
	  
       while(1)

      { 
		ADMUX=0Xc7;      /*  Selected the channel 1, right adjusted, external Aref is selected  */
       ADCSRA=0XE7;     /*  A/D conversion enabled,Conversion started, free running enabled,
           k=3;                interrupt disabled in ADCSRA reg.) , pre-scaler selected       */ 

        while((ADCSRA & (1<<ADIF))==0);    /* Checking whether conversion is finished or not  */ 
       
          i=ADCL;                             /* Moving the 8 bit result to portc from ADCL reg. */
          j=ADCH; 
	lcd_string("TEMPERATURE:");
		i=i/2;
          lcd_showvalue(i);
	if(i>40)
	{
	 PORTA|=0x08;
	 _delay_ms(1000);
	 PORTA=0x00;
	  _delay_ms(1000);
	  PORTB=0x50;
	 
	  
     } 
else if(i<40)
	{
	
	 PORTA=0x00;
	  PORTB=0x00;
	}

	lcd_cmd(0xC0);
	lcd_string("PRESSURE:");
	lcd_showvalue(k++);
     _delay_ms(1000);
	 lcd_gotoxy1(0);

       _delay_ms(500);
	  OSTimeDlyHMSM(0,0,5,0);
      }
}
void task3()
{
	char ch,a[35],i,j;
while(1)
{
	while((UCSR0A&0x80)!=0X80);
	ch=UDR0;
	
if(ch=='$')
{
	while((UCSR0A&0x80)!=0X80);
	ch=UDR0;
		if(ch=='G')
		{
			while((UCSR0A&0x80)!=0X80);
			ch=UDR0;
			if(ch=='P')
			{
				while((UCSR0A&0x80)!=0X80);
				ch=UDR0;
				if(ch=='R')
				{
				while((UCSR0A&0x80)!=0X80);
				ch=UDR0;
				if(ch=='M')
				{
				while((UCSR0A&0x80)!=0X80);
				ch=UDR0;
				if(ch=='C')
				{
					while((UCSR0A&0x80)!=0X80);
					ch=UDR0;
					if(ch==',')
					{
					for(i=0;i<31;i++)
					{
					while((UCSR0A&0x80)!=0X80);
					ch=UDR0;
					a[i]=ch;
					while((UCSR1A&0x20)!=0X20);
					UDR1=a[i];
					}
				}
			}
		}
	}
	}

	}

	}
	OSTimeDly(100);
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

void rec()
{
	char ch,a[35],i,j;
	while((UCSR0A&0x80)!=0X80);
	ch=UDR0;
	
if(ch=='$')
{
	while((UCSR0A&0x80)!=0X80);
	ch=UDR0;
		if(ch=='G')
		{
			while((UCSR0A&0x80)!=0X80);
			ch=UDR0;
			if(ch=='P')
			{
				while((UCSR0A&0x80)!=0X80);
				ch=UDR0;
				if(ch=='R')
				{
				while((UCSR0A&0x80)!=0X80);
				ch=UDR0;
				if(ch=='M')
				{
				while((UCSR0A&0x80)!=0X80);
				ch=UDR0;
				if(ch=='C')
				{
					while((UCSR0A&0x80)!=0X80);
					ch=UDR0;
					if(ch==',')
					{
					for(i=0;i<31;i++)
					{
					while((UCSR0A&0x80)!=0X80);
					ch=UDR0;
					a[i]=ch;
					while((UCSR1A&0x20)!=0X20);
					UDR1=a[i];
					}
				}
			}
		}
	}
	}

	}

	}



}


