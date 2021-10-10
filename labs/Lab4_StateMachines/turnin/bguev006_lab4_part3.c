/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { start, wait, wait2, open, lock} state;

void Tick() {
    switch (state){
        case start:
            state = wait;
            break;
        case wait:
            switch (PINA)
            {
            case 0x04:
                state = wait2;
                break;
            case 0x80:
                state = lock;
                break;
            default:
                state = wait;
                break;
            }
            break;
        case wait2:
            state = PINA == 0x02? open : wait;
            break;
        case open:  
            state = !PINA ? wait : open;
            break;
        case lock:
            state = !PINA ? wait : lock;
            break;
        default:
            state = wait;
            break;
    } // transitions

    switch (state)
    {
    case open:
        PORTB = 0x01;
        break;
    case lock:
        PORTB = 0x00;
        break;
    
    default:
        break;
    }
    //==============DEBUG INFO=================
    PORTC = state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;  //Debug info
    /* Insert your solution below */
    PORTB = 0x00;
    while (1) {
        Tick();
    }
    return 1;
}
