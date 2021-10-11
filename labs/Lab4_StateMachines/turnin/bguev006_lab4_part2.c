/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { start, wait, addwait, subwait, reswait} state;

void Tick() {
    switch (state){
        case start:
            state = wait;
            break;
        case wait:
            switch (PINA)
            {
            case 0x00:
                state = wait;
                break;
            case 0x01:
                if (PORTC < 9) { PORTC++; }
                state = addwait;
                break;
            case 0x02:
                if (PORTC > 0) { PORTC--; }
                state = subwait;
                break;
            case 0x03:
                PORTC = 0x00;
                state = reswait;
            default:
                break;
            }
            break;
        case addwait:
            switch (PINA)
            {
            case 0x00:
                state = wait;
                break;
            case 0x01:
                state = addwait;
                break;
            case 0x03:
                PORTC = 0x00;
                state = reswait;
                break;
            case 0x02:
                if (PORTC > 0) { PORTC--; }
                state = subwait; 
                break;         
            default:
                break;
            }
            break;
        case subwait:
            switch (PINA)
            {
            case 0x00:
                state = wait;
                break;
            case 0x02:
                state = subwait;
                break;
            case 0x03:
                PORTC = 0x00;
                state = reswait;
                break;
            case 0x01:
                if (PORTC < 9) { PORTC++; }
                state = addwait;
                break;
            
            default:
                break;
            }
            break;
        case reswait:
            switch (PINA)
            {
            case 0x00:
                state = wait;
                break;
            case 0x03:
                state = reswait;
                break;
            case 0x01:
                if (PORTC < 9) { PORTC++; }
                state = addwait;
                break;
            case 0x02:
                if (PORTC > 0) { PORTC--; }
                state = subwait;
                break;
            default:
                break;
            }
            break;
        default:
            break;
    } // transitions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    PORTC = 0x07;
    while (1) {
        Tick();
    }
    return 1;
}
