/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 5
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
    /* Insert DDR and PORT initializations */
    DDRC = 0x00; PORTD = 0xFF;
    DDRA = 0xFE; PORTB = 0x01;

    /* Insert your solution below */
    unsigned short currentWeight = 0x0000;
    unsigned char tempB = 0x00;
    while (1) {
        tempB = PINB;
        currentWeight = (PIND << 1) | (tempB & 0x01);

        if (currentWeight > 5 && currentWeight < 70){ // Disarm air bag and turn on warning light
            tempB = (tempB & 0xFD) | 0x04;
        } else if (currentWeight >= 70){ // Arm airbag
            tempB |= 0x02;
        }

        PORTB = tempB;
    }
    return 1;
}
