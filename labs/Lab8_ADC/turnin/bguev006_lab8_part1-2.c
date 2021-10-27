/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 1 & 2
 *	Exercise Description: Converting Analog inputs to Digital inputs by using both a potentiometer
 *  and a light sensor to generate analog inputs.
 *  Video Demo: 
 *      Potentiometer demo: https://youtu.be/Bx0Vi-HOzrY
 *      Light sensor demo: https://youtu.be/ouyLHbCpuiA
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include "timer.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif]

void ADC_init(){
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    ADC_init();

    unsigned short adc_value;
    unsigned char selector;
    while (1) {
        adc_value = ADC;

        selector = (char)ADC;
        PORTB = selector;

        selector = (char)(ADC >> 2);
        PORTD = (selector & 0xC0) >> 6; 
    }
    return 1;
}
