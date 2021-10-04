/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section: 022
 *	Assignment: Lab 2  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    unsigned char tmpB = 0x00;
    unsigned char tmpA = 0x00;

    while(1){
       tmpA = PINA & 0x03; // Reads the input from PA1 and PA0

       if(tmpA == 0x01) {       // If PA1 = 0 and PA0 = 1.
           tmpB = (tmpB & 0xFE) | 0x01;  // Clears rightmost bit and sets it to 1
       } else {
           tmpB = (tmpB & 0xFE) | 0x00;  // Clears rightmost bit and sets it to 0
       }

       PORTB = tmpB;
    }
    return 1;
}
