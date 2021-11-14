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
#include "keypad.h"

//============== SynchSMs setup ==============
task tasks[1];
unsigned short tasksNum = 1;
unsigned short globalPeriod = 100;

//============================================

//------------ Global Variables -------------

//-------------------------------------------

//-------------- Tick functions --------------
int KeypadLightMS(int state){
    unsigned short = GetKeypadKey();
    switch(x){
        case '\0':
            PORTB = 0x1F;
            break;
        case 1:
            PORTB = 0x01;
            break;
        case 2:
            PORTB = 0x01;
            break;
        case 3:
            PORTB = 0x01;
            break;
        case 4:
            PORTB = 0x01;
            break;
        case 5:
            PORTB = 0x01;
            break;
        case 6:
            PORTB = 0x01;
            break;
        case 7:
            PORTB = 0x01;
            break;
        case 8:
            PORTB = 0x01;
            break;
        case 9:
            PORTB = 0x01;
            break;
        case 10:
            PORTB = 0x01;
            break;
        case 'A':
            PORTB = 0x01;
            break;
        case 'B':
            PORTB = 0x01;
            break;
        case 'C':
            PORTB = 0x01;
            break;
        case 'D':
            PORTB = 0x01;
            break;
        case '*':
            PORTB = 0x01;
            break;
        case '0':
            PORTB = 0x01;
            break;
        case '#':
            PORTB = 0x01;
            break;
        default:
            PORTB  = 0x1B;
            break;
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