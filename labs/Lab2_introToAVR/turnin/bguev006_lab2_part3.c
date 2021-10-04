/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section: 022
 *	Assignment: Lab 2  Exercise 3
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
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char availableSpaces = 0x00;
    unsigned char tmpA = 0x00;
    while(1) {
        tmpA = PINA & 0x0F; // Reads the input from PA3 to PA0


        // Writes the number of spaces available on PC3 - PC0
        availableSpaces = 4 -  ((tmpA & 0x01) + ((tmpA & 0x02) >> 1) + ((tmpA & 0x04) >> 2) + ((tmpA & 0x08) >> 3));

        PORTC = availableSpaces & 0x0F; 

        // Sets PC7 to 1 if lot is full, 0 otherwise
        PORTC = ( ( (tmpA & 0x01) && ((tmpA & 0x02) >> 1) && ((tmpA & 0x04) >> 2) && ((tmpA & 0x08) >> 3) ) << 7 ) | PORTC;
    }
    return 1;
}
