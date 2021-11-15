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

#ifndef SCENE_H
#define SCENE_H

typedef struct entity{
    unsigned row_0, col_0; // Initial location
    // Current location
    unsigned char row;
    unsigned char col;
    unsigned char symbol;
}entity;

typedef struct scene{
    entity player;
    unsigned char obstacle_count;
    entity* obstacles;
    unsigned char collision;
    unsigned char pause;
    unsigned char reset;

    const unsigned char* end_msg;
}scene;

#endif
