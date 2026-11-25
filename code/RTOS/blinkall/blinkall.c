#include <includes.h>
#include <avr/interrupt.h>

OS_STK S1[128];
OS_STK S2[128];
OS_STK S3[128];
OS_STK S4[128];

void blink1();
void blink2();
void blink3();
void blink4();


int main()
{
    DDRA = 0xFF; PORTA = 0x00;  // Set Port A as output, initialize to 0
    DDRB = 0xFF; PORTB = 0x00;  // Set Port B as output, initialize to 0
    DDRC = 0xFF; PORTC = 0x00;  // Set Port C as output, initialize to 0
    DDRD = 0xFF; PORTD = 0x00;  // Set Port D as output, initialize to 0

    OSInit(); // Initialize the RTOS

    // Create four tasks with different priorities
    OSTaskCreate(blink1, 0, &S1[127], 4);  // blink1 has priority 4
    OSTaskCreate(blink2, 0, &S2[127], 5);  // blink2 has priority 5
    OSTaskCreate(blink3, 0, &S3[127], 6);  // blink3 has priority 6
    OSTaskCreate(blink4, 0, &S4[127], 7);  // blink4 has priority 7

    // Suspend all tasks except the first one to enforce sequential execution
   // OSTaskSuspend(5);  // Suspend blink2 initially
    OSTaskSuspend(6);  // Suspend blink3 initially
    OSTaskSuspend(7);  // Suspend blink4 initially

    OSStart(); // Start the scheduler, blink1 will run first
}

// Task 1: Toggles PORTA, suspends itself, resumes Task 2
void blink1() {
    while (1) {
        PORTA = ~PORTA;  // Toggle PORTA
        OSTimeDly(61);   // Delay for 61 ticks
        OSTaskSuspend(4); // Suspend Task 1
        OSTaskResume(5);  // Resume Task 2 (blink2)
    }
}

// Task 2: Toggles PORTB, suspends itself, resumes Task 3
void blink2() {
    while (1) {
        PORTB = ~PORTB;  // Toggle PORTB
        OSTimeDly(61);   // Delay for 61 ticks
        OSTaskSuspend(5); // Suspend Task 2
        OSTaskResume(6);  // Resume Task 3 (blink3)
    }
}

// Task 3: Toggles PORTC, suspends itself, resumes Task 4
void blink3() {
    while (1) {
        PORTC = ~PORTC;  // Toggle PORTC
        OSTimeDly(61);   // Delay for 61 ticks
        OSTaskSuspend(6); // Suspend Task 3
        OSTaskResume(7);  // Resume Task 4 (blink4)
    }
}

// Task 4: Toggles PORTD, suspends itself, resumes Task 1
void blink4() {
    while (1) {
        PORTD = ~PORTD;  // Toggle PORTD
        OSTimeDly(61);   // Delay for 61 ticks
        OSTaskSuspend(7); // Suspend Task 4
        OSTaskResume(4);  // Resume Task 1 (blink1)
    }
}
