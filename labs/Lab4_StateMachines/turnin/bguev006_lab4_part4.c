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

enum States { start, wait, hash, hold, open, lock } state;

void Tick() {
    switch (state)
    {
        case start:
            state = wait;
            break;
        case wait:
            switch (PINA)
            {
            case 0x04:
                state = hash;
                break;
            case 0x80:
                state = lock;
                break; 

            default:
                state = wait;
                break;
            }
            break;
        case hash:
            switch (PINA)
            {
            case 0x00:
                state = hold;
                break;
            case 0x04:
                state = hash;
                break;

            default:
                state = wait;
                break;
            }
            break;
        case hold:
            switch (PINA)
            {
            case 0x00:
                state = hold;
                break;
            case 0x02:
                if(!PORTB) { state = open; }    //If door is locked, unlock
                else{ state = lock; }   // If door is unlocked, lock.
                break;
            
            default:
                state = wait;
                break;
            }
            break;
        case open:
            switch (PINA)
            {
            case 0x02:
                state = open;
                break;
            
            default:
                state = wait;
                break;
            }
            break;
        case lock:
            switch (PINA)
            {
            case 0x80:
                state = lock;
                break;
            
            default:
                state = wait;
                break;
            }
            break;
        
        default:
            break;
    }

    switch (state)
    {
        case open:
            PORTB = 0x01;
            break;
        case lock:
            PORTB = 0x00;
        
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
