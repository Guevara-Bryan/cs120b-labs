#ifndef SYNCHSM_H
#define SYNCHSM_H
#include "task.h"
#include <avr/io.h>
#include "timer.h"

task tasks[5];
unsigned short tasksNum = 5;

//============== SynchSMs setup ==============
unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char TLIndex;
const unsigned short globalPeriod = 1;
const unsigned short TLPeriod = 300;
const unsigned short BLPeriod = 1000;
const unsigned short CLPeriod = 300;
const unsigned short SSPeriod = 1;

unsigned short current_note = SSPeriod;
const unsigned char  SOUNDSM = 3;
//============================================

//-------------- Tick functions --------------
int ThreeLEDSM(int state) {
    threeLEDs = 0x01 << TLIndex++;
    if(TLIndex == 3){
        TLIndex = 0;
    }
    return state;
}

int BlinkingLEDSM(int state){
    blinkingLED = blinkingLED ? 0x00 : 0x08;
    return state;
}

int CombineLEDs(int state){
    PORTB = threeLEDs | blinkingLED;
    return state;
}

int SoundSM(int state){
    if(~PINA & 0x04){
        PORTB = (PORTB & 0x10) ? (PORTB & 0x0F) : (PORTB | 0x10);
    }
    return state;
}

enum ModState{start, wait, modup, holdup, moddown, holddown};
int ModulateSM(int state){
    switch(state){ // Transitions
        case start:
            state = wait;
            break;
        case wait:
            switch(~PINA & 0x03){
                case 0x00:
                    state = wait;
                    break;
                case 0x01:
                    state = modup;
                    break;
                case 0x02:
                    state = moddown;
                    break;
                default:
                    state = wait;
                    break;
            }
            break;
        case modup:
            state = holdup;
            break;
        case moddown:
            state = holddown;
            break;
        case holdup:
            state = (PINA & 0x01) ? wait : holdup;
            break;
        case holddown:
            state = (PINA & 0x02) ? wait : holddown;
            break;
            
        default:
            break;
    }

    switch(state){ // State Actions
        case modup:
            tasks[SOUNDSM].period = ++current_note;
            tasks[SOUNDSM].elapsedTime = 0;
            break;
        case moddown:
             if (current_note > 1){
                tasks[SOUNDSM].period = --current_note;
                tasks[SOUNDSM].elapsedTime = 0;
            }
            break;
        default:
            break;
    }
    //============= DEBUG INFO =====================
    PORTC = tasks[SOUNDSM].period;
    return state;
}
//--------------------------------------------


void TimerISR(){
    unsigned char i;
    for (i = 0; i < tasksNum; ++i)
    { // Heart of the scheduler code
        if (tasks[i].elapsedTime >= tasks[i].period)
        { // Ready
            tasks[i].state = tasks[i].Tick(tasks[i].state);
            tasks[i].elapsedTime = 0;
        }
        tasks[i].elapsedTime += globalPeriod;
    }
}
#endif