/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *  Video Demo: https://youtu.be/M9W-TUj4WUk
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include "timer.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, lights, press, release, press2} state;

const unsigned char PATTERN[] = {0x01, 0x02, 0x04, 0x02};
unsigned char pattern_index;
unsigned char score;

void Tick() {
    switch (state){
        case start:
            state = lights;
            break;
        case lights: 
            state = (~PINA & 0x01) ? press : lights;
            if (state == press){        // Only execute when moving to the "press" state.
                // Update score
                if (PORTB == PATTERN[1]) { score++; }
                else if (score > 0) { score--; }

                //Update display
                if (score < 9) {
                    LCD_Cursor(1);
                    LCD_WriteData(score + '0');
                } else {
                    LCD_DisplayString(1, "You win!!");
                }
            }
            break;
        case press:
            state = (~PINA & 0x01) ? press : release;
            break;
        case release: 
            state = (~PINA & 0x01) ? press2 : release;
            if(score >= 9 && state == press2) { score = 0x00; LCD_ClearScreen(); }
            break;
        case press2: 
            state = (~PINA & 0x01) ? press2 : lights;
            break;
        default:
            break;
    } // Transitions

    switch (state){
        case start:
            PORTB = 0x00;
            pattern_index = 0x00;
            break;
        case lights: 
            PORTB = PATTERN[(pattern_index++)%4];
            break;
        case press2: 
            PORTB = PATTERN[(pattern_index++)%4];
            break;
        default:
            break;
    } // State actions.
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    const short PERIOD = 300; // In milliseconds
    TimerSet(PERIOD);

    TimerOn();

    LCD_init();

    state = start;
    LCD_WriteData(0 + '0');
    while (1) {
        Tick();

        while(!TimerFlag) {}
        TimerFlag = 0;
    }
    return 1;
}
