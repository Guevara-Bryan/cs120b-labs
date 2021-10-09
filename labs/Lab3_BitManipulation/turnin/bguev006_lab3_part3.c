/*	Author: Bryan Guevara
 *  Partner(s) Name: Bryan Guevara
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 3
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
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    unsigned char fuelLevel = 0x00;
    unsigned char safety = 0x00;

    while (1) {
        fuelLevel = PINA & 0x0F;
        safety = PINA & 0xF0;

        if (fuelLevel == 0){
            PORTC = 0x00;
        }
        else if (fuelLevel <= 2)
        {
            PORTC = 0x20;
        }
        else if (fuelLevel <= 4)
        {
            PORTC = 0x30;
        }
        else if (fuelLevel <= 6)
        {
            PORTC = 0x38;
        }
        else if (fuelLevel <= 9)
        {
            PORTC = 0x3C;
        }
        else if (fuelLevel <= 12)
        {
            PORTC = 0x3E;
        }
        else
        {
            PORTC = 0x3F;
        }
        
        PORTC |= (!(PORTC & 0x0F)) << 6;    // Sets PC6 to 1 if fuel is <= 4.
        PORTC |= ((safety & 0x10) && (safety & 0x20) && !(safety & 0x40)) << 7; // Sets PC7 to 1 if key is in the ignition, driver is seated and seatbelt is not fastened.
    }
    return 1;
}
