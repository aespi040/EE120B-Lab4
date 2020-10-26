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



//BRU(btn release unlock), BRL(btn rel. lock), STEP1 = unlock pt1, STEP2 = lock pt1
enum States{START, LOCK, UNLOCK, BRU, BRL, STEP1, STEP2} state;
unsigned char count; //keeps track of sequence
unsigned char sequence[] = {4,1,2,1}; //steps shortcutted

void Tick() {
	switch(state) {
		case START:
			state = LOCK; break;
	        default:
			state = START; break;

		case LOCK:
			count = 0;
			if(PINA == sequence[count]) {
				state = BRU; //if 0x04 press then move onto next
			}
			break;

		case BRU:
			if(PINA == 0x00) {
				count++;
				state = STEP1;
			}
			else if(PINA == sequence[count]) { state = BRU; }
			else {state = LOCK;}
			break;

		case STEP1:
			if(count == 4) { state = UNLOCK; } //seq. completed
			else if(PINA == 0x00) { state = STEP1; } //go back to step1
			else if(PINA == sequence[count]) { state = BRU; } 
			else { state = LOCK; } //failed seq. so unlock
			break;
		case UNLOCK:
			count = 0; //resets sequence
			if(PINA == 0x80) { state = LOCK; } //its now locked
			else if (PINA == sequence[count]) { 
				state = BRL; //move onto lock sequence step1
			}
			break;




		case BRL:
			if(PINA == 0x00) {
                                count++;
                                state = STEP2;
			}
			else if(PINA == sequence[count]) { state = BRL; }
                        else {state = UNLOCK;}
			break;

                case STEP2:
                        if(count == 4) { state = LOCK; } //seq. completed
			else if(PINA == 0x80) {state = LOCK; }
                        else if(PINA == 0x00) { state = STEP2; } //go back to step2
                        else if(PINA == sequence[count]) { state = BRL; }
                        else { state = UNLOCK; } //failed to lock so doesnt lock 
                        break;

	}


	switch(state) {
		case START: break;
		default: break;
		case LOCK:
		case BRU:
		case STEP1:
			 PORTB = 0x00;
			 break;
		case UNLOCK:
		case BRL:
		case STEP2: 
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
