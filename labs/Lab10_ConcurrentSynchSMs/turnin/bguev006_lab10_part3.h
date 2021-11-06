#ifndef SYNCHSM_H
#define SYNCHSM_H
#include "task.h"
#include <avr/io.h>
#include "timer.h"

task tasks[4];
unsigned short tasksNum = 4;

//============== SynchSMs setup ==============
unsigned char threeLEDs;
unsigned char blinkingLED;
unsigned char TLIndex;
const unsigned short globalPeriod = 1;
const unsigned short TLPeriod = 300;
const unsigned short BLPeriod = 1000;
const unsigned short CLPeriod = 300;
const unsigned short SSPeriod = 2;
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