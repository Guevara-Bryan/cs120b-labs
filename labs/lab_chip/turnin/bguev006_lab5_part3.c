/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: Festive lights pattern
 *  VIDEO DEMO: https://youtu.be/tYzefcjkwyI
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { start, wait, next, hold} state;
unsigned char pattern;

void Tick() {
    switch (state)
    {
    case start:
        state = wait;
        break;
    
    case wait:
        state = (PINA & 0x01) ? wait : next;
        break;
    
    case next:
        state = (PINA & 0x01) ? wait : hold;
        break;

    case hold: 
        state = (PINA & 0x01) ? wait : hold;
        break;

    default:
        break;
    }

    switch (state)
    {
    case start:
        PORTB = 0x00;
        PORTA = 0xFF;
        pattern = 0x00;
        break;

    case next:
        pattern = (pattern & 0x01) ? (pattern << 1) : (pattern << 1) | 0x01;
        if (pattern == 0x00) { pattern++; }
        PORTB = (pattern & 0x3F) | pattern;
        break;

    default:
        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    state = start;
    while (1) {
        Tick();
    }
    return 1;
}
