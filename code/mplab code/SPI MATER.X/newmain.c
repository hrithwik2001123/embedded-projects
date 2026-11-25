/*
 * File:   newmain.c
 * Author: user
 *
 * Created on 26 November, 2024, 11:09 AM
 */


#include <xc.h>

void main(void) {
    TRISC=0X80;
    RCSTA=0X90;
    SPBRG=25;
    TXSTA=0X24;
    return;
}
