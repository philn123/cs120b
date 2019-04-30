/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 6 Exercise 2
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}
void TimerISR(){
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet( unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void Tick();
enum States {INIT, ONE, TWO, THREE, SET, RESET} state;
int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; // Init port B to 0s
	TimerSet(50);
	TimerOn();
	state = INIT;
    while (1) 
    {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
		
    }
}

void Tick(){
	switch(state){
		case INIT:
			state = ONE;
			break;
		case ONE:
			if((PINA & 0x01) == 0x01){
				state = SET;
			}
			else{
				state = TWO;
			}
			break;
		case TWO:
			if((PINA & 0x01) == 0x01){
				state = SET;
			}
			else{
				state = THREE;
			}
			break;
		case THREE:
			if((PINA & 0x01) == 0x01){
				state = SET;
			}
			else{
				state = ONE;
			}
			break;
		case SET:
			if((PINA & 0x01) == 0x01){
				state = SET;
			}
			else{
				state = RESET;
			}
			break;
		case RESET:
			if((PINA & 0x01) == 0x01){
				state = ONE;
			}
			else{
				state = RESET;
			}
			break;
		default:
			break;
	}
	
	switch(state){
		case INIT:
			PORTB = 0x00;
			break;
		case ONE:
			PORTB = 0x01;
			break;
		case TWO:
			PORTB = 0x02;
			break;
		case THREE:
			PORTB = 0x04;
			break;
		case SET:
			break;
		case RESET:
			break;
		default:
			break;
	}
	
	
	
}



