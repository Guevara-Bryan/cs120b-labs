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
        DDRB = 0x00; PORTB = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
        PORTC = (  (PORTA & 0x01) +
                   ((PORTA & 0x02) >> 1)+
                   ((PORTA & 0x04) >> 2)+
                   ((PORTA & 0x08) >> 3)+
                   ((PORTA & 0x10) >> 4)+
                   ((PORTA & 0x20) >> 5)+
                   ((PORTA & 0x40) >> 6)+
                   ((PORTA & 0x80) >> 7)+
                   
                   (PORTB & 0x01) +
                   ((PORTB & 0x02) >> 1)+
                   ((PORTB & 0x04) >> 2)+
                   ((PORTB & 0x08) >> 3)+
                   ((PORTB & 0x10) >> 4)+
                   ((PORTB & 0x20) >> 5)+
                   ((PORTB & 0x40) >> 6)+
                   ((PORTB & 0x80) >> 7)
                );
    }
    return 1;
}
