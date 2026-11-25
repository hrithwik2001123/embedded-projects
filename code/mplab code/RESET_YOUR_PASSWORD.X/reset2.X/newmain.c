#pragma config FOSC = XT, WDTE = OFF, PWRTE = OFF, BOREN = OFF, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF
#include <xc.h>
#include <string.h>
#define _XTAL_FREQ 4000000

char *success_msg = "Success";
char *fail_msg = "FAIL";
char *enter_pass_msg = "ENTER PASSWORD:";
char *reset_pass_msg = "Enter new password:";
char *confirm_pass_msg = "Confirm password:";
char *reset_success_msg = "Password Reset!";
char *size="max only 10 character";
void next()
{
    TXREG='\r';
    while(!(TRMT));
    TXREG='\n';
    return;
}
void print(const char *s) {
    while (*s) {
        TXREG = *s++;
        while (!TRMT);
        __delay_ms(50); 
    }
    while (!TRMT);
    next();
}

void get_input(char *buffer) {
   int i;
    for( i=0;;i++)
     {
        while (!RCIF); 
        buffer[i] = RCREG;
        if (buffer[i] == '\r')
        { buffer[i] = '\0'; 
        break;
        }
        TXREG = buffer[i++];
        while (!TRMT);
    }
    buffer[i] = '\0'; 
    next();
}
void reset_password(char *password) {
    char new_pass[11], confirm_pass[11];
    print(reset_pass_msg);
    print(size);
    get_input(new_pass);
    print(confirm_pass_msg);
    get_input(confirm_pass);
    if (strcmp(new_pass, confirm_pass) == 0) {
        strcpy(password, new_pass);
        print(reset_success_msg);
        while(1);
    } else {
        print(fail_msg);
    }
}

void main() {
    char password[10] = "HRITHWIK", input[10];
    TRISC = 0x80; RCSTA = 0x90; SPBRG = 25; TXSTA = 0x24;

    while (1) {
        print(enter_pass_msg);
        get_input(input);
        if (strcmp(password, input) == 0) {
            print(success_msg);
        } else {
            print(fail_msg);
            reset_password(password);
        }
    }
}
