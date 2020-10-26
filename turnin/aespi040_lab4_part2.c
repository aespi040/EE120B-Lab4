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




enum States{START, WAIT, ADD, SUB, RESET} state;
unsigned char count;

void Tick() {
	switch(state) {
		case START:
			count = 7;
			state = WAIT; break;
	        default:
			state = START; break;

		case WAIT:
			if(PINA == 1) {
				state = ADD;
			       if(count < 9) {
				       count++;
			       }
			}
			else if (PINA == 0x02) {
				state = SUB;
				if( count > 0){ count--; }
			}
			else if(PINA == 0x03) {
				state = RESET;
				count =0;
			}
			break;

		case ADD:
			if(PINA == 0) { state = WAIT; }
			else if(PINA == 0x02) { 
				state = SUB;
				if(count > 0) {
					count--;
				}
			}
			else if(PINA == 0x03) {
				state = RESET;
				count = 0;
			}
			else {}
			break;
		case SUB:
			if(PINA == 0x00) { state = WAIT;}
			else if(PINA == 0x01) {
				state = ADD;
				if(count < 9) {
					count++;
				}
			}
			else if(PINA == 0x03) {
				state = RESET;
				count = 0;
			}
			break;
		case RESET:
                        if(PINA == 0x00) { state = WAIT;}
                        break;
	}


	switch(state) {
		case START: break;
		default: break;
		case WAIT:
		case ADD:
		case SUB:
		case RESET:
			PORTC = count;
			break;
	}
}




int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
	state = START;
	count = 0x07;

    while (1) {
	    Tick(); 
    }
    return 1;
}
