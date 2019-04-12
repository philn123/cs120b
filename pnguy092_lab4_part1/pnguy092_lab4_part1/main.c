/*
 * pnguy092_lab4_part1.c
 *
 * Created: 4/12/2019 10:39:27 AM
 * Author : iiNza
 */ 

#include <avr/io.h>
void Tick();
enum States{START, ONE, WAIT, TWO, WAIT2} state;

int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
	state = START; //initial state
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
	
	
	
	
	
	
	
}

