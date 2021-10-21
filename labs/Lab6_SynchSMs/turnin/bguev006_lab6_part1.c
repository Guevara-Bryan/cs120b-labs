/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  Video Demo: 
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

enum States {start, wait, lights} state;

unsigned char pattern;

void Tick() {
    switch (state){
        case start:
            state = wait;
            break;
        case wait:
            state = lights;
            break;
        case lights: 
            state = lights;
            break;
        default:
            break;
    } // Transitions

    switch (state){
        case wait:
            PORTB = 0x00;
            pattern = 0x00;
            break;
        case lights: 
            pattern = pattern == 4 || pattern == 0 ? 0x01 : pattern << 1;
            PORTB = pattern;
            break;
        default:
            break;
    } // State actions.
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

    const short PERIOD = 1000; // In milliseconds
    TimerSet(PERIOD);

    TimerOn();

    state = start;
    while (1) {
        Tick();

        while(!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
