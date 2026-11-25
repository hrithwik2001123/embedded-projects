/*
**************************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*
*                                             AVR Sample code
* File        : TEST.C
* By          : Julius Luukko
* Version     : V1.0
*
* AVR-GCC port version : 141003
*
* Description :
*
*         This file contains a simpler example program showing how to use the AVR port of uC/OS-II.
*         This program needs below 1 kB of RAM, so all the MCUs with at least 1 kB of internal SRAM
*         should work with this. A bit over 4 kB of program memory is needed. Additionally the MCU 
*         should have INT0 and INT1 pins. Therefore this example does not work directly with ATmega169.
*         This program has been tested with ATmega128 and ATmega163.
*         
*         Two external interrupts are used to signal two tasks, which toggle the state of a led.
*         The external INT pins are in port D pins 2 and 3 (except for the megas 103, 64 and 128, where
*         they are in pins 0 and 1). Connect a 10-wire cable supplied with the STK500 from PORTD header
*         to SWITCHES header and another cable from PORTB header to LEDS header. Now pressing either 
*         SW2 or SW3 (SW0 or SW1 with mega103, 64 and 128) switch should toggle the state of the respective 
*         led.
*
**************************************************************************************************************
*/

#include "includes.h"
#include "adi_UART.h"
#include<util/delay.h>
/*
*************************************************************************************************************
* - If the selected MCU does not have enough internal SRAM and no external memory interface,
* notify the user.
* - Define which are the external interrupt pins.
* - Define the value of TCCR0, which sets the clock divider to 1024 for timer0
*************************************************************************************************************
*/

#if defined(__AVR_AT90S2313__) || defined(__AVR_AT90S2333__) || defined(__AVR_AT90S4433__) || \
        defined(__AVR_AT90S4434__) || defined(__AVR_AT90S8535__) || defined(___AVR_ATmega8535__)
# error "Your MCU probably does not have enough SRAM to run this program"
#elif defined(__AVR_AT90S4414__) 
# error "Your MCU probably does not have enough program memory to run this program"
#elif defined(__AVR_AT90S8515__) || \
       defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__) || defined(__AVR_ATmega163__) || \
       defined(___AVR_ATmega8515__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
       defined(__AVR_ATmega8__)
#   define PIN_INT0 2
#   define PIN_INT1 3
#   define TCCR0VAL (_BV(CS02) | _BV(CS00))
#elif defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega103__)
#   define PIN_INT0 0
#   define PIN_INT1 1
#   define TCCR0VAL (_BV(CS02) | _BV(CS01) | _BV(CS00))
#else
#  error "Don't know what kind of MCU you are compiling for"
#endif

/*
**************************************************************************************************************
*                                               CONSTANTS
**************************************************************************************************************
*/

#define TASK_STK_SIZE  OS_TASK_DEF_STK_SIZE            /* Size of each task's stacks (# of bytes)          */
#define TASK_START_PRIO 0
#define TASK_1_PRIO     2
#define TASK_2_PRIO     5

#define TASK_1_PIN      PIN_INT0
#define TASK_2_PIN      PIN_INT1

/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/

OS_STK          Task1Stk[TASK_STK_SIZE];        /* Task1 stack                                     */
OS_STK          Task2Stk[TASK_STK_SIZE];        /* Task2 stack                                     */
OS_STK          TaskStartStk[TASK_STK_SIZE];    /* TaskStartTask stack                             */
OS_EVENT       *Task1Sem;                       /* Semaphore to notify Task1 from ISR              */
OS_EVENT       *Task2Sem;                       /* Semaphore to notify Task2 from ISR              */
OS_EVENT       *PortBSem;                       /* Semaphore to get exclusive access to PORTB      */

/*
**************************************************************************************************************
*                                           FUNCTION PROTOTYPES
**************************************************************************************************************
*/

void  Task1(void *data);                                /* Function prototypes of tasks                     */
void  Task2(void *data);                                /* Function prototypes of tasks                     */

/*
**************************************************************************************************************
*                                                MAIN
**************************************************************************************************************
*/

int main (void)
{
	uart_init();
	tx_strng("Start main...\n");
  	OSInit();

  OSTaskCreate(Task1, (void *)0, (void *)&Task1Stk[TASK_STK_SIZE - 1], TASK_1_PRIO);
	OSTaskCreate(Task2, (void *)0, (void *)&Task2Stk[TASK_STK_SIZE - 1], TASK_2_PRIO);
  OSStart();                                          /* Start multitasking                               */
  return 0;
}

void Task1(void * data)
{
	DDRC = 0xff;
	PORTC = 0xff;
	while(1) {
		tx_strng("t a s k 1\n");
		PORTC ^= 0xff;
		OSTaskSuspend(OS_PRIO_SELF);
	}
}

void Task2(void * data)
{
	while(1) {
		tx_strng("TASK2\n");
		OSTaskResume(2);
	}
}


