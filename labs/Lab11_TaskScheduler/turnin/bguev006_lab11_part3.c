/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 3
 *	Exercise Description: Display keypad input on LCD
 *  Video Demo: https://youtu.be/P3EYlP5pvsk
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
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    unsigned char i = 0;
    tasks[i].state = gk_start;
    tasks[i].period = GetKeySMPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &GetKeySM;
    i++;
    tasks[i].state = 0;
    tasks[i].period = DisplayKeySMPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &DisplayKeySM;


    LCD_init();
    TimerSet(globalPeriod);
    TimerOn();
    while (1) { }
    return 1;
}
