/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section: 022
 *	Assignment: Lab 2  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;

    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    unsigned char tmpC = 0x00;
    while(1) {
        //Reading the inputs from pins a, b, and c
        tmpA = PINA;
        tmpB = PINB;
        tmpC = PINC;


        // Sets PD7-PD2 to an approximation of the weight of the cars.
        PORTD = ((tmpA + tmpB + tmpC) & 0xF0) >> 2;



        if((tmpA + tmpB + tmpC) > 0x8C){        // If sum is greater than 140.
            PORTD |= 0x01;           //Sets PD0 to 1
        } else {
            PORTD &= 0xFE;           //Clears PD0
        }


        //Sets PD1 = 1 if |A - C| > 80, 0 otherwise.
        if (tmpA - tmpC > 80 || tmpC - tmpA > 80)
        {
            PORTD |= 0x02;
        }
        else
        {
            PORTD &= 0xFD;
        }
        
    }
    return 1;
}
