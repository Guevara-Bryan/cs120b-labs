/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 5
 *	Exercise Description: Obstacle avoiding game
 *  Video Demo: 
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
#include "scene.h"


//============== SynchSMs setup ==============
task tasks[8];
unsigned short tasksNum = 8;
unsigned short globalPeriod = 25;

unsigned short buttonUpPeriod = 50;
unsigned short buttonDownPeriod = 50;
unsigned short pauseButtonPeriod = 50;

unsigned short obstacleScrollerPeriod = 300;
unsigned short displayObstaclesPeriod = 300;

unsigned short displayPlayerPeriod = 50;
unsigned short sceneResetPeriod = 100;
unsigned short collisionDetectorPeriod = 100;
//============================================

//------------ Global Variables -------------
const unsigned char screen_width = 16;
scene current_scene;
//-------------------------------------------

//-------------- Tick functions --------------
enum ButtonUpStates { bu_start, bu_wait, bu_press };
int ButtonUpSM(int state){
    if(!current_scene.pause){
        unsigned char up_button = ~PINA & 0x01;
        switch (state){
        case bu_start:
            state = bu_wait;
            break;
        case bu_wait: 
            state = up_button ? bu_press : bu_wait;
            if(state == bu_press) { current_scene.player.row = 1; }
            break;
        case bu_press:
            state = up_button ? bu_press : bu_wait;
            break;
        default:
            state = bu_wait;
            break;
        }
    }
    return state;
}

enum ButtonDownStates { bd_start, bd_wait, bd_press };
int ButtonDownSM(int state){
    if(!current_scene.pause){
        unsigned char down_button = ~PINA & 0x02;
        switch (state){
        case bd_start:
            state = bd_wait;
            break;
        case bd_wait: 
            state = down_button ? bd_press : bd_wait;
            if(state == bd_press) { current_scene.player.row = 2; }
            break;
        case bd_press:
            state = down_button ? bd_press : bd_wait;
            break;
        default:
            state = bd_wait;
            break;
        }
    }
    return state;
}

enum PauseButtonStates {p_start, p_off, p_presson, p_on, p_pressoff, };
int PauseButtonSM(int state){
    unsigned char pause_button = ~PINA & 0x04;

    //--------------- If pause set by collision ---------------------------
    if(current_scene.collision && current_scene.pause) { state = p_on; }
    //---------------------------------------------------------------------

    switch(state) {
        case p_start:
            state = p_off;
            break;
        case p_off:
            state = pause_button ? p_presson : p_off;
            break;
        case p_presson:
            state = pause_button ? p_presson : p_on;
            break;
        case p_on:
            state = pause_button ? p_pressoff : p_on;
            break;
        case p_pressoff:
            state = pause_button ? p_pressoff : p_off;
            break;  
        default:
            state = p_off;
            break;
    }

    switch(state) {
        case p_on:
        case p_presson:
            current_scene.pause = 1;
            break;
        case p_off:
        case p_pressoff:
            if (current_scene.pause && current_scene.collision) { 
                current_scene.collision = 0;
                LCD_ClearScreen();
            }
            current_scene.pause = 0;
            break;
        default:
            current_scene.pause = 0;
            break;
    }
    return state;
}

int ObstacleScrollerSM(int state){
    if(!current_scene.pause){
        for (unsigned char i = 0; i < current_scene.obstacle_count; i++){
            current_scene.obstacles[i].col--;
            if(current_scene.obstacles[i].col < 1){
                current_scene.obstacles[i].col = 16;//current_scene.obstacles[i].col_0;
            }
        }
    }

    return state;
}

int CollisionDetectorSM(int state){
    if(!current_scene.pause){
        for(unsigned char i = 0; i < current_scene.obstacle_count; i++){
            if(current_scene.player.col == current_scene.obstacles[i].col){
                if(current_scene.player.row == current_scene.obstacles[i].row){
                    current_scene.collision = 1;
                    break;
                }
            }
        }
    }

    return state;
}

int DisplayPlayerSM(int state){
    if (!current_scene.pause){
        unsigned char x, y;
        x = current_scene.player.col - 1;
        y = ((current_scene.player.row - 1) * screen_width) + 1;
        LCD_Cursor(y + x);
    }
    return state;
}

int DisplayObstaclesSM(int state){
    if (!current_scene.pause) {
        unsigned char x, y;

        //------------------- Display obstacles. ------------------------------
        for (unsigned char i = 0; i < current_scene.obstacle_count; i++){
            x = current_scene.obstacles[i].col - 1;
            y = ((current_scene.obstacles[i].row - 1) * screen_width) + 1;
            // Clear previous location
            if(x < (screen_width - 1)){
                LCD_Cursor(y + x + 1);
                LCD_WriteData(' ');
            } else if (x == (screen_width - 1)){
                LCD_Cursor(y);
                LCD_WriteData(' ');
            }
            // Move to new location
            if(x < screen_width){
                LCD_Cursor(y + x);
                LCD_WriteData(current_scene.obstacles[i].symbol);
            }
        }

        if(current_scene.collision){
            LCD_ClearScreen();
            LCD_DisplayString(3, current_scene.end_msg);
            LCD_Cursor(0); // Hide cursor off the screen.
            current_scene.pause = 1;
            current_scene.reset = 1;
        }
    }
    return state;
}

int SceneResetSM(int state){
    if(current_scene.reset){
        //------------------ Reset 'reset' flag -------------
        current_scene.reset = 0;

        //------------------ Reset position of all entity positions -------------
        current_scene.player.col = current_scene.player.col_0;
        current_scene.player.row = current_scene.player.row_0;

        for (unsigned char i = 0; i < current_scene.obstacle_count; i++){
            current_scene.obstacles[i].col =  current_scene.obstacles[i].col_0;
            current_scene.obstacles[i].row =  current_scene.obstacles[i].row_0;
        }
    }
    return state;
}
//--------------------------------------------

//---------------- Initialize SMS ----------------
void SynchSM_init(){
    unsigned char i = 0;
    const unsigned char start = 0;

    tasks[i].state = start;
    tasks[i].period = buttonUpPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &ButtonUpSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = buttonDownPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &ButtonDownSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = pauseButtonPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &PauseButtonSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = obstacleScrollerPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &ObstacleScrollerSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = collisionDetectorPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &CollisionDetectorSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = displayObstaclesPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &DisplayObstaclesSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = displayPlayerPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &DisplayPlayerSM;
    i++;
    tasks[i].state = start;
    tasks[i].period = sceneResetPeriod;
    tasks[i].elapsedTime = tasks[i].period;
    tasks[i].Tick = &SceneResetSM;
}
//------------------------------------------------

//################# Scheduler ####################
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