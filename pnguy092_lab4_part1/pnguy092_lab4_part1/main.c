<<<<<<< HEAD
/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 4 Exercise 1
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
enum States{START, ONE, WAIT, TWO, WAIT2} state;
void Tick();
=======
/*
 * pnguy092_lab4_part1.c
 *
 * Created: 4/12/2019 10:39:27 AM
 * Author : iiNza
 */ 

#include <avr/io.h>
void Tick();
enum States{START, ONE, WAIT, TWO, WAIT2} state;
>>>>>>> dba29d3dcbb57240e68d9748a76802bd60ec06ba

int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
<<<<<<< HEAD
=======
	state = START; //initial state
>>>>>>> dba29d3dcbb57240e68d9748a76802bd60ec06ba
    while (1) 
    {
		Tick();
    }
}

void Tick(){
	switch(state){ //transitions
		case START:
			state = ONE;
			break;
<<<<<<< HEAD
		case ONE:
			if((PINA & 0x01) == 0x01){
				state = WAIT;
			}
			else{
				state = ONE;
			}
			break;
		case WAIT:
			if((PINA & 0x01) == 0x01){
				state = WAIT;
			}
			else{
				state = TWO;
			}
			break;
		case TWO:
			if((PINA & 0x01) == 0x01){
				state = WAIT2;
			}
			else{
				state = TWO;
			}
			break;
		case WAIT2:
			if((PINA & 0x01) == 0x01){
				state = WAIT2;
			}
			else{
				state = ONE;
			}
			break;
					
		default:
			break;
	}
	switch(state){ //actions
		case START:
			PORTB = 0x01;
			break;
		case ONE:
			PORTB = 0x01;
			break;
		case WAIT:
			PORTB = 0x02;
			break;
		case TWO:
			PORTB = 0x02;
			break;
		case WAIT2:
			PORTB = 0x01;
			break;
		default:
			break;	
	}
=======
		
		case ONE:
			
		
		default:
			break;
		
	}
	
	switch(state){ //state actions
		case START:
			PORTB = 0x01;
			break;
		
		case ONE:
			PORTB = 0x01;
			break;
			
		case WAIT:
			PORTB = 0x02;
			break;
		
		case TWO:
			PORTB = 0x02;
			break;
		
		case WAIT2:
			PORTB = 0x01;
			break;
			
		default:
			break;
		
	}
	
	
	
	
	
	
	
>>>>>>> dba29d3dcbb57240e68d9748a76802bd60ec06ba
}

