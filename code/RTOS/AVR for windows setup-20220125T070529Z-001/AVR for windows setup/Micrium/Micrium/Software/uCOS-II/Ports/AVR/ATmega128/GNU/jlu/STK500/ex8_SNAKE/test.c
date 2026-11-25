/************************************************************************************************************** 
Description: This file contains a demo example created to exhibit how various OS attributes can be used to 
develop a game of Snake (with minimalistic features). This example gives a very preliminary and important 
overview of  real time application design.
**************************************************************************************************************/

#include "includes.h"
#include <stdio.h>
#include "VT102lib.h" //Gtkterm driver

/**************************************************************************************************************
* - If the selected MCU does not have enough internal SRAM and no external memory interface,
* notify the user.
* - Define the value of TCCR0, which sets the clock divider to 1024 for timer0
************************************************************************************************************/

#if defined(__AVR_AT90S2313__) || defined(__AVR_AT90S2333__) || defined(__AVR_AT90S4433__) || \
        defined(__AVR_AT90S4434__) || defined(__AVR_AT90S8535__) || defined(___AVR_ATmega8535__)
# error "Your MCU probably does not have enough SRAM to run this program"
#elif defined(__AVR_AT90S4414__) 
# error "Your MCU probably does not have enough program memory to run this program"
#elif defined(__AVR_AT90S8515__) || \
       defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__) || defined(__AVR_ATmega163__) || \
       defined(___AVR_ATmega8515__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) || \
       defined(__AVR_ATmega8__)
#   define TCCR0VAL (_BV(CS02) | _BV(CS00))
#elif defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega103__)
#   define TCCR0VAL (_BV(CS02) | _BV(CS01) | _BV(CS00))
#else
#  error "Don't know what kind of MCU you are compiling for"
#endif


/***************************************************************************************************************
*                                               CONSTANTS
**************************************************************************************************************/
#define TASK_STACK 512
#define XVAL 0
#define YVAL 1

/*************************************************************************************************************
*			                                    Prototypes
*************************************************************************************************************/
void Task1( void *Task1Data ); //Highest priority task (for updating score)
void Task2( void *Task2Data ); //Intermediate priority task (for generating snake food)
void Task3( void *Task3Data ); //Lowest priority task (for moving the snake)
INT8U random(INT8U n); //Random number generator would be used by the food generator task

/*************************************************************************************************************
                                            GLOBAL VARIABLES
**************************************************************************************************************/
volatile INT8U xt=0,yt=0;
INT32U          RndNext;                                /* Used by random generator                         */

OS_STK Task1Stack[ TASK_STACK ];
OS_STK Task2Stack[ TASK_STACK ];
OS_STK Task3Stack[ TASK_STACK ];

OS_EVENT *MsgBox_score; //This message mailbox is intended for use by Task 1 and Task 3 for communicating updates on the score
OS_EVENT *MsgBox_axis; //This message mailbox is intended for use by ISR and Task 3 for communicating the X & Y axis of joystick

OS_EVENT         *xSem; //This semaphore is to protect the global variable xt
OS_EVENT         *ySem; //This semaphore is to guard the global variable yt
extern OS_EVENT  *pSem; //This semaphore has been declared in VT102lib.h to guard VT library since UART is a shared resource

/************************************************************************************************************/

int main(void) 
{

    //Configuring UART1 for communication with GTKterm
    UART_config(115200);
    
    //Enabling internal pullup to avoid false triggering
    DDRE=0x00;
    PORTE=0xFF;
    	
	OSInit(); //required for generating the idle task and statistic task
	
	//UART, xt and yt guarding semaphore creation in unlocked state
	xSem  = OSSemCreate(1); 
	ySem  = OSSemCreate(1);
	pSem  = OSSemCreate(1);
	
	//Message mailboxes creation in locked state
	MsgBox_score = OSMboxCreate( (void *)0 );
	MsgBox_axis = OSMboxCreate( (void *)0 );
	
	//Creating tasks
	OSTaskCreate( Task1, (void *)0, &Task1Stack[ TASK_STACK - 1 ], 0 );
	OSTaskCreate( Task2, (void *)0, &Task2Stack[ TASK_STACK - 1 ], 1 );
	OSTaskCreate( Task3, (void *)0, &Task3Stack[ TASK_STACK - 1 ], 2 );

	OSStart(); //Start multi-tasking
	
	return 0;
}

void Task1( void *Task1Data ) 
{
    INT8U score=0,err;
    INT8U *temp;
    
    unsigned char str1[3];
	Task1Data = Task1Data;
	
	//Starting the clock tick by enabling timer interrupt
	OS_ENTER_CRITICAL();
	TCCR0=TCCR0VAL;                                         /* Set TIMER0 prescaler to CLK/1024                 */
	TIMSK=_BV(TOIE0);                                   /* Enable TIMER0 overflow interrupt                 */
	TCNT0=256-(CPU_CLOCK_HZ/OS_TICKS_PER_SEC/1024);     /* Set the counter initial value                    */
	OS_EXIT_CRITICAL();

    // Selecting Y-axis of joystick value initially
	ADMUX =0XE2;
	ADCSRA=0XEE;
	SREG = SREG | 0x80;
	
	//Clearing the Gtkterm initially and displaying score as 0
	VT102DispClrScr();
	VT102DispStr (2,2,"SCORE:",COLOR_RED, COLOR_CYAN);	
    sprintf(str1,"%d",score);
    VT102DispStr (8,2,str1,COLOR_RED, COLOR_CYAN);
    
	for(;;) 
	{
        //Pend from mailbox into score
        temp = (INT8U *)OSMboxPend(MsgBox_score,0,&err); //Blocking call (infinite time)
        //VT102DispStr (8,2,"SCORE UPDATED",COLOR_RED, COLOR_CYAN);
        score=*temp;
        sprintf(str1,"%d",score);
        VT102DispStr (8,2,str1,COLOR_RED, COLOR_CYAN);               
	}
}

// Snake food generator
void Task2( void *Task2Data ) 
{
    INT8U err;
    Task2Data = Task2Data;

	for(;;) 
	{
	    //clearing previous instance of food
	    VT102DispChar(xt+5, yt+5,' ', COLOR_BLUE, COLOR_BLUE); 
	    
	    OSSemPend(ySem, 0, &err);
	    yt = random(15);
	    OSSemPost(ySem);
	    
	    OSSemPend(xSem, 0, &err);
        xt = random(71);
        OSSemPost(xSem);
		
		VT102DispChar(xt+5, yt+5,'@', COLOR_BLACK, COLOR_WHITE);
		
		//block for predecided interval (4s)  
		OSTimeDlyHMSM(0, 0, 50, 0); 
	}
	
}

void Task3( void *Task3Data ) 
{
    INT8U score_local=0;
    INT8U x2=10,x3=10,x4=10,x5=10,y2=11,y3=12,y4=13,y5=14; 
    volatile INT8U x1=10,y1=10;
    volatile INT8U x1_new=0,y1_new=0;
    INT8U adcval_x,adcval_y;
    INT8U xt_local=0,yt_local=0;
    INT8U err;
    INT8U *temp;
    
    Task3Data = Task3Data;

    VT102DispChar(x1, y1,'*', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x2, y2,'-', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x3, y3,'-', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x4, y4,'-', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x5, y5,'-', COLOR_BLACK, COLOR_RED);
    
	
	for(;;) 
	{
	    //determine new positions after pending the axis mailbox for Y
	    temp=(INT8U *)OSMboxPend(MsgBox_axis,0,&err); //Blocking call (infinite time)
	    adcval_y=*temp;
	    if(adcval_y>165)
	    {
	        
	        y1_new=(y1_new-1);
			(y1_new<4)?y1_new=20:y1_new;
			
		}
		else if(adcval_y<90)
		{
		    y1_new=(y1_new+1);
			(y1_new>20)?y1_new=4:y1_new;
		}
		else
		    y1_new=y1; //remains unchanged
	    
	    //determine new positions after pending the axis mailbox for X    
	    temp=(INT8U *)OSMboxPend(MsgBox_axis,0,&err); //Blocking call (infinite time)
	    adcval_x=*temp;
	    if(adcval_x>165)
	    {
	        x1_new=(x1_new-1);
			(x1_new<4)?x1_new=76:x1_new;
		}
		else if(adcval_x<90)
		{
		    x1_new=(x1_new+1);
			(x1_new>76)?x1_new=4:x1_new;
		}
		else
		    x1_new=x1; //remains unchanged
	    
	    //clearing previous instance of snake
	    VT102DispChar(x5, y5,' ', COLOR_BLUE, COLOR_BLUE); 
	    VT102DispChar(x1_new, y1_new,'*', COLOR_BLACK, COLOR_RED); //creating new instance of snake
        VT102DispChar(x2, y2,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
        VT102DispChar(x1_new, y1_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
        VT102DispChar(x1_new, y1_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
        VT102DispChar(x1_new, y1_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
        
        //Acquire semaphores for using global variables
        OSSemPend(ySem, 0, &err);
        yt_local=yt+5;
        OSSemPost(ySem);
        
        OSSemPend(xSem, 0, &err);
        xt_local=xt+5;
        OSSemPost(xSem);
               
        //update score mailbox if required
        if((x1_new==xt_local) && (y1_new==yt_local))
        {
            score_local++;
            temp=&score_local;
            OSMboxPost(MsgBox_score,(void *) temp);
        }
        
        //recording current position of snake so that it can be cleared next time
        x1=x1_new;
        y1=y1_new;
    }
	
}

ISR(ADC_vect)
{
    INT8U joystick_val=0;
    INT8U *temp1;
    static INT8U axis=1;
    static INT16U cnt=0;
    cnt++;
    if(cnt==400)
    {
        cnt=0;
        joystick_val = ADCH;
        if(axis==YVAL)
        {
            axis=XVAL;
            ADMUX=0xE1;
            //Post to mailbox for Y-axis
            temp1=&joystick_val;
            OSMboxPost(MsgBox_axis,(void *) temp1);
         }
        else
        {
            axis=YVAL;
            ADMUX=0xE2;  
            //Post to mailbox for X-axis
            temp1=&joystick_val;
            OSMboxPost(MsgBox_axis,(void *) temp1);
        }       
    }
    ADCSRA=0XEE;
}

INT8U random (INT8U n)
{
    RndNext = RndNext * 1103515245 + 12345;
    return ((INT8U)(RndNext / 256) % (n + 1));
}

