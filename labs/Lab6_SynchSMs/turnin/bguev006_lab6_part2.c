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

enum States {start, lights, press, release, press2} state;

const unsigned char PATTERN[] = {0x01, 0x02, 0x04, 0x02};
unsigned char pattern_index;

void Tick() {
    switch (state){
        case start:
            state = lights;
            break;
        case lights: 
            state = (~PINA & 0x01) ? press : lights;
            break;
        case press:
            state = (~PINA & 0x01) ? press : release;
            break;
        case release: 
            state = (~PINA & 0x01) ? press2 : release;
            break;
        case press2: 
            state = (~PINA & 0x01) ? press2 : lights;
            break;
        default:
            break;
    } // Transitions

    switch (state){
        case start:
            PORTB = 0x00;
            pattern_index = 0x00;
            break;
        case lights: 
            PORTB = PATTERN[(pattern_index++)%4];
            break;
        case press2: 
            PORTB = PATTERN[(pattern_index++)%4];
            break;
        default:
            break;
    } // State actions.
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

    const short PERIOD = 300; // In milliseconds
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
