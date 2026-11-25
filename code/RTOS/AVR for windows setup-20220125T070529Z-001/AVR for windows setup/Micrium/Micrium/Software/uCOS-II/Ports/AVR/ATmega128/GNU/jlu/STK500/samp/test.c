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
#define TASK_1_PRIO     1
#define TASK_2_PRIO     10

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
void  TaskStart(void *data);                            /* Function prototypes of Startup task              */
void  AvrInit(void);                                    /* Initialize AVR                                   */

/*
**************************************************************************************************************
*                                                MAIN
**************************************************************************************************************
*/

int main (void)
{
	uart_init();
	tx_strng("Start main...\n");
  AvrInit();                                         /* Initialize the AVR UART and Timer                 */
  OSInit();
  //Task1Sem = OSSemCreate(1);                         /* Initialize notification semaphores to 0           */
  //Task2Sem = OSSemCreate(0);
  //PortBSem = OSSemCreate(1);                         /* Initialize resource semaphore to 1                */

  OSTaskCreate(TaskStart, (void *)0, (void *)&TaskStartStk[TASK_STK_SIZE - 1], TASK_START_PRIO);

  OSStart();                                          /* Start multitasking                               */
  return 0;
}

/*
**************************************************************************************************************
*                                              STARTUP TASK
**************************************************************************************************************
*/

void TaskStart (void *data)
{

  data = data;                                        /* Prevent compiler warning                         */

  /* 
   * Timer interupt is enabled here, not before OSStart()!
   */

  OS_ENTER_CRITICAL();
  TCCR0=TCCR0VAL;                                         /* Set TIMER0 prescaler to CLK/1024                 */
  TIMSK=_BV(TOIE0);                                   /* Enable TIMER0 overflow interrupt                 */
  TCNT0=256-(CPU_CLOCK_HZ/OS_TICKS_PER_SEC/1024);     /* Set the counter initial value                    */
  OS_EXIT_CRITICAL();

  /* 
   * Create the tasks end delete this task
   */
    
  OSTaskCreate(Task1, (void *)0, (void *)&Task1Stk[TASK_STK_SIZE - 1], TASK_1_PRIO);
  OSTaskCreate(Task2, (void *)0, (void *)&Task2Stk[TASK_STK_SIZE - 1], TASK_2_PRIO);

  OSTaskDel(OS_PRIO_SELF);
}

/*
**************************************************************************************************************
*                                                  TASKS
**************************************************************************************************************
*/
void Task1 (void *data)
{
  INT8U err;

  for (;;) {
  	tx_char('a');
    OSSemPend(Task1Sem, 0, &err);                  /* Wait for the semaphore signal */
    PORTB ^= 1<<TASK_1_PIN;
    tx_strng("#1111111111111111111111111111111111111111#\n");
    OSTimeDly(2);
    OSSemPost(Task1Sem);
    tx_char('b');
  }
}

void Task2 (void *data)
{
  INT8U err;

  for (;;) {
  	tx_char('j');
    OSSemPend(Task1Sem, 0, &err);                  /* Wait for the semaphore signal */
    PORTB ^= 1<<TASK_2_PIN;
    tx_strng("!222222222222222222222222222222222222222!\n");
    OSSemPost(Task1Sem);
    tx_char('k');
  }
}


/*
**************************************************************************************************************
*                                                  INTERRUPT SERVICE ROUTINES
**************************************************************************************************************
*/

/*
 *
 * See the file README for the description of the general ISR format.
 *
 */

UCOSISR(SIG_INTERRUPT0)
{
  PushRS();
  OSIntEnter();
  if (OSIntNesting == 1)
    OSTCBCur->OSTCBStkPtr = (OS_STK *)SP;

  sei();
  OSSemPost(Task1Sem);                            /* Notify Task1 */
  OSIntExit();
  PopRS();
}

UCOSISR(SIG_INTERRUPT1)
{
  PushRS();
  OSIntEnter();
  if (OSIntNesting == 1)
    OSTCBCur->OSTCBStkPtr = (OS_STK *)SP;

  sei();
  OSSemPost(Task2Sem);                            /* Notify Task2 */
  OSIntExit();
  PopRS();
}

void AvrInit (void)
{
  DDRB=0xff;                                      /* Init PortB for output to LEDS of the STK500    */
  DDRD=0x00;                                      /* Init PortD for input to SWITCHES of the STK500 */
  PORTB=0xff;                                     /* Turn all the leds off                          */

#if defined(EIMSK)
  EIMSK=0;
#elif defined(GIMSK)
  GIMSK=0;
#elif defined(GICR)
  GICR=0;
#else
#   error("Don't known the name of interrupt control register")
#endif


#if defined(EICRA)
  EICRA=_BV(ISC11) | _BV(ISC01);                  /* Falling edge generates SIG_INTERRUPT0 and 1    */
#else
  MCUCR=_BV(ISC11) | _BV(ISC01);                  /* Falling edge generates SIG_INTERRUPT0 and 1    */
#endif

#if defined(EIMSK)
  EIMSK=_BV(INT1) | _BV(INT0);
#elif defined(GIMSK)
  GIMSK=_BV(INT1) | _BV(INT0);
#elif defined(GICR)
  GICR=_BV(INT1) | _BV(INT0);
#endif
  
}
