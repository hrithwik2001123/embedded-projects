//////////////////  INCLUDES HEADER FILES  ////////////////////////////////
#include<includes.h>	//for RTOS
#include<avr/io.h>
#include<util/delay.h>

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

OS_STK task1stk[512];
OS_STK task2stk[512];



void task1();
void task2();

int main()
{

	OSInit();
	
	UCSR0C=0x06;
	UCSR0B=0x18;
	UBRR0L=51;
	UBRR0H=0x00;
	
	
	OSTaskCreate(task1,(void *)0,&task1stk[511],1);
	
	OSTaskCreate(task2,(void *)0,&task2stk[511],2);
	
	
	
	OSStart();
	
	return 0;
	



}

void task1()
{

	while(1)
	{
		while(!(UCSR0A&0x20));
		
		UDR0='A';
		OSTaskSuspend(1);
	
	}


}

void task2()
{

	while(1)
	{
		while(!(UCSR0A&0x20));
		
		UDR0='B';
		OSTaskResume(1);
	
	}


}








