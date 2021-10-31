/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 3
 *	Exercise Description: 5 second melody. I added some code for debuggin to the timerISR() function. 
 *  Video Demo: https://youtu.be/W5nVqnUsOSI
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include "timer.h"
#include "pwm.h"
#include "task.h"


#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


//================= SynchSM setup =============
task tasks[2];
const unsigned short tasksNum = 2;
const unsigned short tasksPeriodGCD = 50;
const unsigned short periodPlay = tasksPeriodGCD * 2;
const unsigned short periodAdvance = tasksPeriodGCD;
unsigned char ticker;
unsigned char aticker;
//============================================

//------------------ Notes Code--------------------------------
const double SILENT = 0.0,
             C4 = 261.63,
             D4 = 293.66,
             E4 = 329.63,
             F4 = 349.23,
             G4 = 392.00,
             A4 = 440.00,
             B4 = 493.88,
             C5 = 523.25;
double tune[] = { D4, F4, G4, F4, D4, C4, D4, F4, D4};
unsigned short note_index;
const unsigned short MAX_INDEX = 8;
const unsigned char DURATION = 50; // 5 seconds;
//------------------------------------------------------------

//---------------- Tick function prototypes ------------------
enum PlayStates
{
    p_start,
    p_off,
    p_play,
    p_hold
};
int playTick(int state);
enum AdvanceStates
{
    a_start,
    a_off,
    a_next
};
int advanceTick(int state);
//-----------------------------------------------------------

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    unsigned char i = 0;

    tasks[i].state = p_start;
    tasks[i].period = periodPlay;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &playTick;
    i++;
    tasks[i].state = a_start;
    tasks[i].period = periodAdvance;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &advanceTick;

    note_index = 0;
    aticker = ticker = 0;
    PWM_on();
    TimerSet(tasksPeriodGCD);
    TimerOn();
    
    while (1) {}

    return 1;
}

//################### FUNCTION DEFINITIONS ###########################

void TimerISR() // DECLARED IN timer.h
{
    unsigned char i;
    for (i = 0; i < tasksNum; ++i)
    { // Heart of the scheduler code
        if (tasks[i].elapsedTime >= tasks[i].period)
        { // Ready
            tasks[i].state = tasks[i].Tick(tasks[i].state);
            tasks[i].elapsedTime = 0;
        }
        tasks[i].elapsedTime += tasksPeriodGCD;
    }
    //================= DEBUGGING =================================
    PORTC = (unsigned char)(note_index & 0x00FF);
}


int playTick(int state)
{
    switch(state)
    { // Transitions
    case p_start:
        state = p_off;
        break;
    case p_off:
        state = (~PINA & 0x01) ? p_play : p_off;
        break;
    case p_play:
        if(ticker >= DURATION) { state = p_hold; }
        break;
    case p_hold:
        state = (~PINA & 0x01) ? p_hold : p_off;
        break;
    }

    switch (state)
    { // State Actions
    case p_off:
    case p_hold:
        set_PWM(SILENT);
        note_index = 0;
        ticker = 0;
        aticker = 0;
        break;
    case p_play:
        set_PWM(tune[note_index]);
        ticker++;
        break;
    }
    return state;
}


int advanceTick(int state)
{
    if (!(++aticker % 11)){
        note_index += note_index < MAX_INDEX ? 1 : 0;
    } 
    return state;
}