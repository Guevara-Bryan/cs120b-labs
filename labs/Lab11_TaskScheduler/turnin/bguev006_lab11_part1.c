/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 4
 *	Exercise Description: Display keypad input on LCD
 *  Video Demo: https://youtu.be/HywmiLLF67U
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "SynchSMs.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    /* Insert your solution below */

    unsigned char i = 0;
    tasks[i].state = 0;
    tasks[i].period = globalPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &KeypadLightMS;

    TimerSet(globalPeriod);
    TimerOn();
    while (1) { }
    return 1;
}
