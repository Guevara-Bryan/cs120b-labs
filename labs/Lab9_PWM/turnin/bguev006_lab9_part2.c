/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 2
 *	Exercise Description: Going up and down notes from C4 to C5
 *  Video Demo: https://youtube.com/shorts/ED0KO6dHtq8?feature=share
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
const unsigned char tasksPeriodGCD = 100;
const unsigned char periodPlay = 100;
const unsigned char periodAdvance = 100;
//============================================

//------------------ Notes Code--------------------------------
// C4, D4, E4, F4, G4, A4, B4, C5
double notes[] = { 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25 };
unsigned char note_index;
const unsigned char MAX_INDEX = 7;
const double SILENT = 0.00;
//------------------------------------------------------------

//---------------- Function prototypes ------------------
enum PlayStates
{
    p_start,
    p_off,
    p_presson,
    p_pressoff,
    p_on
};
int playTick(int state);
enum AdvanceStates
{
    a_start,
    a_wait,
    a_inc,
    a_dec
};
int advanceTick(int state);
//-----------------------------------------------------------

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
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
    PWM_on();
    TimerOn();
    TimerSet(tasksPeriodGCD);
    


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
}


int playTick(int state)
{
    switch(state)
    { // Transitions
    case p_start:
        state = p_off;
        break;
    case p_off:
        state = (~PINA & 0x01) ? p_presson : p_off;
        break;
    case p_presson:
        state = (~PINA & 0x01) ? p_presson : p_on;
        break;
    case p_pressoff:
        state = (~PINA & 0x01) ? p_pressoff : p_off;
        break;
    case p_on:
        state = (~PINA & 0x01) ? p_pressoff : p_on;
        break;
    }

    switch (state)
    { // State Actions
    case p_off:
    case p_pressoff:
        set_PWM(SILENT);
        break;
    case p_presson:
    case p_on:
        set_PWM(notes[note_index]);
        break;
    }
    return state;
}


int advanceTick(int state)
{
    switch (state)
    { // Transitions
        case a_start:
            state = a_wait;
            break;
        case a_wait:
            switch (PINA)
            {
            case 0xFD:
                state = a_inc;
                note_index += note_index < MAX_INDEX ? 1 : 0;
                break;
            case 0xFB:
                state = a_dec;
                note_index -= note_index > 0 ? 1 : 0;
                break;
            default:
                state = a_wait;
                break;
            }
            break;
        case a_inc:     
            state = PINA == 0xFF ? a_wait : a_inc;     
            break;
        case a_dec:
            state = PINA == 0xFF ? a_wait : a_dec;
            break;
        default:
            state = a_wait;
            break;
    }
    return state;
}