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

enum States { start, wait, collect, reg, eval, hold, lock} state;
enum States previous;
unsigned char nPress = 0x00;

unsigned char key[] = {0x04, 0x01, 0x02, 0x01};
unsigned char uKey[4];

void Tick() {
    switch (state)
    {
        case start:
            state = wait;
            nPress = 0x00;
            break;
        
        case wait:
            nPress = 0x00;
            if(PINA){
                state = collect;
            } else if (PINA == 0x80) { state = lock; }
            else { state = wait; }
            break;
        case collect: 
            if (!PINA && nPress < 4){
                state = collect;
            } else if (PINA && nPress < 4){
                state = reg;
            } else {
                state = eval;
            }
            break;
        case reg:
            if (PINA) { state = reg; }
            else { state = collect; }
            break;
        case eval:
            if (previous == eval) { state = hold; }
            else { state = eval; }
            break;
        case hold:
            if (!PINA) { state = wait; }
            else {state = hold;}
            break;
        case lock:
            state = wait;
            break;

        default:
            state = wait;
            break;
    }

    switch (state)
    {
        case collect:
            if (uKey[0] && previous == reg) { nPress++; }
            previous = collect;
            break;
        case reg:
            if (PINA) { uKey[nPress] = PINA; }
            previous = reg;
            break;
        case eval:
            PORTB = 0x01;
            for (int i = 0; i < nPress; i++){
                PORTB = key[i] == uKey[i];
                if(!PORTB) { break; }
            }
            previous = eval;
            break;
        case lock:
            PORTB = 0x00;
        
        default:
            break;
    }
    
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    PORTB = 0x00;
    state = start;
    nPress = 0x00;
    while (1) {
        Tick();
    }
    return 1;
}
