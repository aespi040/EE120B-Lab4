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




enum States{START, LOCK, STEP1, STEP2, UNLOCK} state;
unsigned char count;

void Tick() {
	switch(state) {
		case START:
			state = LOCK; break;
	        default:
			state = START; break;

		case LOCK:
			if(PINA == 0x04) {
				state = STEP1;
			}
			break;
		case STEP1:
			if(PINA == 0x00) { state = STEP2; }
			else if(PINA == 0x04) { state = STEP1; }
			else { state = LOCK; }
			break;
		case STEP2:
			if(PINA == 0x02) { state = UNLOCK; }
                        else if(PINA == 0x00) { state = STEP2; }
                        else { state = LOCK; }
                        break;
		case UNLOCK:
			if(PINA == 0x80) { state = LOCK; }
			break;
	}


	switch(state) {
		case START: break;
		default: break;
		case LOCK:
		case STEP1:
		case STEP2:
			 PORTB = 0x00;
			 break;
		case UNLOCK:
			 PORTB = 0x01;
			 break;
	}
}




int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	state = START;
        

    while (1) {
	    Tick(); 
    }
    return 1;
}
