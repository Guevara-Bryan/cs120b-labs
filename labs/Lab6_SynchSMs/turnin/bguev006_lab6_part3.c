/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  Video Demo: https://youtu.be/tpQxpT7s54g
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include "timer.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { start, wait, addwait, subwait, reswait} state;
unsigned char tick_counter;

void Tick() {
    switch (state){
        case start:
            state = wait;
            break;
        case wait:
            tick_counter = 0x00;
            switch (~PINA & 0x03)
            {
            case 0x00:
                state = wait;
                break;
            case 0x01:
                if (PORTB < 9) { PORTB++; }
                state = addwait;
                break;
            case 0x02:
                if (PORTB > 0) { PORTB--; }
                state = subwait;
                break;
            case 0x03:
                PORTB = 0x00;
                state = reswait;
            default:
                break;
            }
            break;
        case addwait:
            switch (~PINA & 0x03)
            {
            case 0x00:
                state = wait;
                break;
            case 0x01:
                if (PORTB < 9) {
                    if (tick_counter++ > 9){
                        PORTB++;
                        tick_counter = 0x00;
                        break;
                    }
                } 
                state = addwait;
                break;
            case 0x03:
                PORTB = 0x00;
                state = reswait;
                break;
            case 0x02:
                if (PORTB > 0) { PORTB--; }
                state = subwait; 
                break;         
            default:
                break;
            }
            break;
        case subwait:
            switch (~PINA & 0x03)
            {
            case 0x00:
                state = wait;
                break;
            case 0x02:
                if (PORTB > 0) {
                    if (tick_counter++ > 9){
                        PORTB--;
                        tick_counter = 0x00;
                        break;
                    }
                }              
                state = subwait;
                break;
            case 0x03:
                PORTB = 0x00;
                state = reswait;
                break;
            case 0x01:
                if (PORTB < 9) { PORTB++; }
                state = addwait;
                break;
            
            default:
                break;
            }
            break;
        case reswait:
            switch (~PINA & 0x03)
            {
            case 0x00:
                state = wait;
                break;
            case 0x03:
                state = reswait;
                break;
            case 0x01:
                if (PORTB < 9) { PORTB++; }
                state = addwait;
                break;
            case 0x02:
                if (PORTB > 0) { PORTB--; }
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
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

    const short PERIOD = 100; // In milliseconds

    TimerSet(PERIOD);

    TimerOn();

    state = start;
    PORTB = 0x07;
    tick_counter = 0x00;
    while (1) {
        Tick();

        while(!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
