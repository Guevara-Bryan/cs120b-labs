/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { start, state1, onpress1, state2, onpress2} state;

void Tick() {
    switch (state){
        case start:
            state = state1;
            break;
        case state1:
            state = (PINA & 0x01) ? onpress1 : state1;
            break;
        case state2:
            state = (PINA & 0x01) ? onpress2 : state2;
            break;
        case onpress1:
            state = (PINA & 0x01) ? onpress1 : state2;
            break;
        case onpress2:
            state = (PINA & 0x01) ? onpress2 : state1;
            break;
        default:
            break;
    } // transitions

    switch (state){
        case state1:
        case onpress2:
            PORTB = 0x01;
            break;
        case state2:
        case onpress1:
            PORTB = 0x02;
            break;
        default:
            break;
    } // state actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
