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
#include "pwm.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, wait, note1, note2, note3} state;
const double NOTE1 = 392.00, // G
             NOTE2 = 440.00, // A
             NOTE3 = 493.88, // B
             SILENT = 0.00;

const unsigned short PERIOD = 60;

void Tick(){
    switch (state){
        case start:
            state = wait;
            break;
        case wait:
            switch (PINA)
            {
            case 0xFE:
                state = note1;
                break;
            case 0xFD:
                state = note2;
                break;
            case 0xFB:
                state = note3;
                break;
            default:
                state = wait;
                break;
            }
            break;
        case note1:
            state = PINA == 0xFE ? note1 : wait;
            break;
        case note2:
            state = PINA == 0xFD ? note2 : wait;
            break;
        case note3:
            state = PINA == 0xFB ? note3 : wait;
            break;
        default:
            state = wait;
            break;
    } // transitions

    switch (state) {
        case start:
            break;
        case wait:
            set_PWM(SILENT);
            break;
        case note1:
            set_PWM(NOTE1);
            break;
        case note2:
            set_PWM(NOTE2);
            break;
        case note3:
            set_PWM(NOTE3);
            break;
    } // state actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    TimerOn();
    TimerSet(PERIOD);
    PWM_on();
    state = start;
    while (1) {
        Tick();

        while(!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
