/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 3
 *	Exercise Description: Turn light on if the photoresistor detects half of the amount of light it can detect.
 *  NOTE: I used ambient light as the value for MAX_LIGHT, which was 27.
 *  Video Demo: 
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

    const unsigned short MAX_LIGHT = 0x001B;
    while (1) {
        adc_value = ADC;

        PORTB = adc_value >= MAX_LIGHT ? 0x01 : 0x00;
    }
    return 1;
}
