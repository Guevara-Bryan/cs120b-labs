/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 5
 *	Exercise Description: Obstacle avoiding game
 *  Video Demo: https://youtu.be/LmCpZW0-euU
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "SynchSMs.h"
#include "stdlib.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    
    LCD_init();
    TimerSet(globalPeriod);
    TimerOn();

    //---------------- Game Scene Starting Setup ---------------------------------
    current_scene.obstacle_count = 3;
    current_scene.obstacles = (entity*) calloc(current_scene.obstacle_count, sizeof(entity));

    current_scene.end_msg = "Game Over!";
    current_scene.player.col = current_scene.player.col_0 = 3;
    current_scene.player.row = current_scene.player.row_0 = 1;
    current_scene.obstacles[0].symbol = '#';
    current_scene.obstacles[0].row_0 = 1;
    current_scene.obstacles[0].col_0 = 17; // Place them just off the screen
    current_scene.obstacles[1].symbol = '#';
    current_scene.obstacles[1].row_0 = 2;
    current_scene.obstacles[1].col_0 = 20; // Place them just off the screen.
    current_scene.obstacles[2].symbol = '#';
    current_scene.obstacles[2].row_0 = 1;
    current_scene.obstacles[2].col_0 = 25; // Place them just off the screen.

    for (unsigned char i = 0; i < current_scene.obstacle_count; i++){
        current_scene.obstacles[i].col =  current_scene.obstacles[i].col_0;
        current_scene.obstacles[i].row =  current_scene.obstacles[i].row_0;
    }

    current_scene.collision = 0;
    current_scene.pause = 0;
    current_scene.reset = 0;
    //--------------------------------------------------------------

    SynchSM_init();

    while (1) { }

    free(current_scene.obstacles);
    return 1;
}
