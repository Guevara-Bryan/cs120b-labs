/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 4
 *	Exercise Description: ThreLED BlinkingLED using concurrent state machines.
 *  And speaker plus two buttons to modulate the frequency up and down.
 *  Video Demo: https://youtu.be/oa1UKYloaWE
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "io.h"
#include "SynchSMs.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    unsigned char i = 0;

    tasks[i].state = 0;
    tasks[i].period = TLPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &ThreeLEDSM;
    i++;
    tasks[i].state = 0;
    tasks[i].period = BLPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &BlinkingLEDSM;
    i++;
    tasks[i].state = 0;
    tasks[i].period = CLPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &CombineLEDs;
    i++;
    tasks[i].state = 0;
    tasks[i].period = SSPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &SoundSM;
    i++;
    tasks[i].state = 0;
    tasks[i].period = globalPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &ModulateSM;


    TLIndex = 0;
    TimerOn();
    TimerSet(globalPeriod);
    

    while (1) {}
    return 1;
}
