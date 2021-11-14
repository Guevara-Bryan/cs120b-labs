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

#ifndef SYNCHSM_H
#define SYNCHSM_H
#include "task.h"
#include <avr/io.h>
#include "timer.h"
#include "io.h"
#include "keypad.h"

//============== SynchSMs setup ==============
task tasks[2];
unsigned short tasksNum = 2;
unsigned short globalPeriod = 50;


unsigned short GetKeySMPeriod = 200;
unsigned short DisplayKeySMPeriod = 100;
//============================================

//------------ Global Variables -------------
unsigned char display_char;
unsigned char lcd_update = 0;
//-------------------------------------------

//-------------- Tick functions --------------
enum GKStates { gk_start, gk_wait, gk_press};
int GetKeySM(int state){
    unsigned char pressed_char = GetKeypadKey();
    switch (state)
    {
    case gk_start:
        state = gk_wait;
        break;
    case gk_wait: 
        state = pressed_char == '\0' ? gk_wait : gk_press;
        if(state == gk_press) { display_char = pressed_char; }
        break;
    case gk_press:
        state = pressed_char == '\0' ? gk_wait : gk_press;
        if(state == gk_wait) { lcd_update = 1; }
        break;
    default:
        state = gk_wait;
        break;
    }
    return state;
}

int DisplayKeySM(int state){
    if (lcd_update){
        lcd_update = 0;
        LCD_Cursor(1);
        LCD_WriteData(display_char);
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