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
void Task3( void *Task3Data ); //Intermediate priority task (for signalling the food generator task)
void Task4( void *Task4Data ); //Lowest priority task (for moving the snake)
INT8U random(INT8U n); //Random number generator would be used by the food generator task

/*************************************************************************************************************
                                            GLOBAL VARIABLES
**************************************************************************************************************/
volatile INT8U xt=0,yt=0;
INT32U          RndNext;                                /* Used by random generator                         */

OS_STK Task1Stack[ TASK_STACK ];
OS_STK Task2Stack[ TASK_STACK ];
OS_STK Task3Stack[ TASK_STACK ];
OS_STK Task4Stack[ TASK_STACK ];

OS_EVENT *MsgBox_score; //This message mailbox is intended for use by Task 1 and Task 3 for communicating updates on the score
OS_EVENT *MsgBox_axis; //This message mailbox is intended for use by ISR and Task 3 for communicating the X & Y axis of joystick

OS_EVENT         *xSem; //This semaphore is to protect the global variable xt
OS_EVENT         *ySem; //This semaphore is to guard the global variable yt
OS_EVENT         *tSem; //This semaphore is to signal the food generator task (using semaphore as an event flag)
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
	//tSem is used as an event flag
	xSem  = OSSemCreate(1); 
	ySem  = OSSemCreate(1);
	pSem  = OSSemCreate(1);
	tSem  = OSSemCreate(1);
	
	//Message mailboxes creation in locked state
	MsgBox_score = OSMboxCreate( (void *)0 );
	MsgBox_axis = OSMboxCreate( (void *)0 );
	
	//Creating tasks
	OSTaskCreate( Task1, (void *)0, &Task1Stack[ TASK_STACK - 1 ], 0 );
	OSTaskCreate( Task2, (void *)0, &Task2Stack[ TASK_STACK - 1 ], 1 );
	OSTaskCreate( Task3, (void *)0, &Task3Stack[ TASK_STACK - 1 ], 2 );
    OSTaskCreate( Task4, (void *)0, &Task4Stack[ TASK_STACK - 1 ], 3 );
	
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
		
		//block for predecided interval (4s) or till food is eaten up  
		OSSemPend(tSem, 0, &err);
	}
	
}

void Task3( void *Task3Data ) 
{
    Task3Data = Task3Data;
    for(;;)
    {
       //Block for some time to give a chance to the snake generator task to execute
        OSTimeDlyHMSM(0, 0, 50, 0);
        OSSemPost(tSem);    
    }
}

void Task4( void *Task4Data ) 
{
    INT8U score_local=0;
    INT8U x2=10,x3=10,x4=10,x5=10,y2=11,y3=12,y4=13,y5=14; 
    volatile INT8U x1=10,y1=10;
    volatile INT8U x5_new=10,y5_new=14,x4_new=10,y4_new=13,x3_new=10,y3_new=12,x2_new=10,y2_new=11,x1_new=10,y1_new=10;
    INT8U adcval_x,adcval_y;
    INT8U xt_local=0,yt_local=0;
    INT8U err;
    INT8U *temp;
    
    Task4Data = Task4Data;

    VT102DispChar(x1, y1,'*', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x2, y2,'-', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x3, y3,'-', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x4, y4,'-', COLOR_BLACK, COLOR_RED);
    VT102DispChar(x5, y5,'-', COLOR_BLACK, COLOR_RED);
    
	
	for(;;) 
	{
	
	    //recording current position of snake tail so that it can be cleared next time
        x5=x5_new;
        y5=y5_new;
        x4=x4_new;
        y4=y4_new;
        x3=x3_new;
        y3=y3_new;
        x2=x2_new;
        y2=y2_new;
        x1=x1_new;
        y1=y1_new;
	    
	    //determine new positions after pending the axis mailbox for Y
	    temp=(INT8U *)OSMboxPend(MsgBox_axis,0,&err); //Blocking call (infinite time)
	    adcval_y=*temp;
	    if(adcval_y>165)
	    {
	        x5_new=x4_new;
	        x4_new=x3_new;
	        x3_new=x2_new;
	        x2_new=x1_new;
	        y5_new=y4_new;
	        y4_new=y3_new;
	        y3_new=y2_new;
	        y2_new=y1_new; 	        
	        y1_new=(y1_new-1);
			(y1_new<4)?y1_new=20:y1_new;
			
			//clearing previous instance of snake
	        VT102DispChar(x5, y5,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x4, y4,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x3, y3,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x2, y2,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1, y1,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1_new, y1_new,'*', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x2_new, y2_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x3_new, y3_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x4_new, y4_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x5_new, y5_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
			
		}
		else if(adcval_y<90)
		{
		    x5_new=x4_new;
	        x4_new=x3_new;
	        x3_new=x2_new;
	        x2_new=x1_new;
	        y5_new=y4_new;
	        y4_new=y3_new;
	        y3_new=y2_new;
	        y2_new=y1_new;
		    y1_new=(y1_new+1);
			(y1_new>20)?y1_new=4:y1_new;
			
			//clearing previous instance of snake
	        VT102DispChar(x5, y5,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x4, y4,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x3, y3,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x2, y2,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1, y1,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1_new, y1_new,'*', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x2_new, y2_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x3_new, y3_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x4_new, y4_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x5_new, y5_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
		}
			    
	    //determine new positions after pending the axis mailbox for X    
	    temp=(INT8U *)OSMboxPend(MsgBox_axis,0,&err); //Blocking call (infinite time)
	    adcval_x=*temp;
	    if(adcval_x>165)
	    {
            x5_new=x4_new;
	        x4_new=x3_new;
	        x3_new=x2_new;
	        x2_new=x1_new;
	        y5_new=y4_new;
	        y4_new=y3_new;
	        y3_new=y2_new;
	        y2_new=y1_new;
	        x1_new=(x1_new-1);
			(x1_new<4)?x1_new=76:x1_new;
			
			//clearing previous instance of snake
	        VT102DispChar(x5, y5,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x4, y4,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x3, y3,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x2, y2,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1, y1,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1_new, y1_new,'*', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x2_new, y2_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x3_new, y3_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x4_new, y4_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x5_new, y5_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
		}
		else if(adcval_x<90)
		{
		    x5_new=x4_new;
	        x4_new=x3_new;
	        x3_new=x2_new;
	        x2_new=x1_new;
	        y5_new=y4_new;
	        y4_new=y3_new;
	        y3_new=y2_new;
	        y2_new=y1_new;
		    x1_new=(x1_new+1);
			(x1_new>76)?x1_new=4:x1_new;
			
			//clearing previous instance of snake
	        VT102DispChar(x5, y5,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x4, y4,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x3, y3,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x2, y2,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1, y1,' ', COLOR_BLUE, COLOR_BLUE); 
	        VT102DispChar(x1_new, y1_new,'*', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x2_new, y2_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x3_new, y3_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x4_new, y4_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
            VT102DispChar(x5_new, y5_new,'-', COLOR_BLACK, COLOR_RED); //creating new instance of snake
		}
		    
	    //Acquire semaphores for using global variables
        OSSemPend(ySem, 0, &err);
        yt_local=yt+5;
        OSSemPost(ySem);
        
        OSSemPend(xSem, 0, &err);
        xt_local=xt+5;
        OSSemPost(xSem);
               
        //update score mailbox if required
        if((x1==xt_local) && (y1==yt_local))
        {
            score_local++;
            temp=&score_local;
            OSMboxPost(MsgBox_score,(void *) temp);
            OSSemPost(tSem);
        }
        
        
    }
	
}

ISR(ADC_vect)
{
    INT8U joystick_val=0;
    INT8U *temp1;
    static INT8U axis=1;
    static INT16U cnt=0;
    cnt++;
    if(cnt==600)
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

