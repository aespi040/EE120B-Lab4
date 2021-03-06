/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif




enum States{Start, OFF, S1, S2, ON} state;

void Tick() {
	switch(state) {
		case Start:
			state = OFF; break;
	        default:
			state = Start; break;

		case OFF:
			if(PINA == 1) {	state = S1;}
		       	break;
		case S1:
			if(PINA == 0) { state = ON; }
			break;
		case S2:
			if(PINA == 0) { state = OFF;}
			break;
		case ON:
                        if(PINA == 1) { state = S2;}
                        break;
	}


	switch(state) {
		case Start: break;
		default: break;
		case OFF:
			PORTB = 0x01;
			break;
		case S1:
			PORTB = 0x02;
			break;
		case S2:
			PORTB = 0x01;
			break;
		case ON:
			PORTB = 0x02;
			break;
	}
}




int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	state = Start;
    while (1) {
	    Tick(); 
    }
    return 1;
}
