#ifndef SYNCHSM_H
#define SYNCHSM_H
#include "task.h"
#include <avr/io.h>
#include "timer.h"
#include "io.h"
#include <string.h>

task tasks[1];
unsigned short tasksNum = 1;

//============== SynchSMs setup ==============
unsigned short globalPeriod = 300;
//============================================

//-------------- Tick functions --------------
int ScrollStringSM(int state)
{
    const unsigned char string[] = "CS120B is Legend... wait for it DARY!";
    static unsigned char start = 0, end = 1;
    const unsigned char sub_length = end - start;

    const unsigned char substring[sub_length + 1];
    memset(substring, '\0', sub_length + 1);
    strncpy(substring, (string + start), sub_length);

    LCD_DisplayString(17 - sub_length, substring);

    if (*(substring) && end < 16)
    {  
        end++;
    }
    else if(*(substring))
    {
        start++;
        end++;
    }
    else
    {
        end = 1;
        start = 0;
    }
    return state;
}
//--------------------------------------------

void TimerISR()
{
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