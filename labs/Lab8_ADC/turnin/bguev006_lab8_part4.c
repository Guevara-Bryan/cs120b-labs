/*	Author: Bryan Guevara
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 4 (Challenge)
 *  NOTE: I did this part of the lab on a different day. So, the value of the max light on this
 *  day was different than the one used on previouse parts, specifically this day it was 0x0011.
 *	Exercise Description: Using 8 LEDs to display the amount of light received by the
 *  photoresistor.
 *  Video Demo: https://youtu.be/cLihfsFrbc8
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

void ADC_init()
{
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void)
{
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;
    /* Insert your solution below */

    ADC_init();

    unsigned short adc_value;

    const unsigned short MAX_LIGHT = 0x0011;
    while (1)
    {
        adc_value = ADC;

        if (adc_value > (MAX_LIGHT - 3)) { PORTB = 0xFF; }
        else if (adc_value > (MAX_LIGHT - 5)) { PORTB = 0x7F; }
        else if (adc_value > (MAX_LIGHT - 7)) { PORTB = 0x3F; }
        else if (adc_value > (MAX_LIGHT - 9)) { PORTB = 0x1F; }
        else if (adc_value > (MAX_LIGHT - 11)) { PORTB = 0x0F; }
        else if (adc_value > (MAX_LIGHT - 13)) { PORTB = 0x07; }
        else if (adc_value > (MAX_LIGHT - 15)) { PORTB = 0x03; }
        else if (adc_value > (MAX_LIGHT - 17)) { PORTB = 0x01; }
        else { PORTB = 0x00; }
    }
    return 1;
}
