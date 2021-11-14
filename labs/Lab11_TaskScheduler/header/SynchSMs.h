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

#ifndef SYNCHSM_H
#define SYNCHSM_H
#include "task.h"
#include <avr/io.h>
#include "timer.h"
#include "io.h"
#include "keypad.h"

//============== SynchSMs setup ==============
task tasks[1];
unsigned short tasksNum = 1;
unsigned short globalPeriod = 100;

//============================================

//------------ Global Variables -------------

//-------------------------------------------

//-------------- Tick functions --------------

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