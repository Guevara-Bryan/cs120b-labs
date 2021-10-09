/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 1
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
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    unsigned char fuelLevel = 0x00;

    while (1) {
        fuelLevel = PINA & 0x0F;

        if (fuelLevel == 0){
            PORTC = 0x00;
        }
        else if (fuelLevel <= 2)
        {
            PORTC = 0x20;
        }
        else if (fuelLevel <= 4)
        {
            PORTC = 0x30;
        }
        else if (fuelLevel <= 6)
        {
            PORTC = 0x38;
        }
        else if (fuelLevel <= 9)
        {
            PORTC = 0x3C;
        }
        else if (fuelLevel <= 12)
        {
            PORTC = 0x3E;
        }
        else
        {
            PORTC = 0x3F;
        }
        
        PORTC |= (!(PORTC & 0x0F)) << 6;
    }
    return 1;
}
