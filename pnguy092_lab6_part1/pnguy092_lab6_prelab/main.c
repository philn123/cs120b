/*
 * pnguy092_lab6_prelab.c
 *
 * Created: 4/22/2019 8:41:54 PM
 * Author : iiNza
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
enum States {INIT, ONE, TWO, THREE} state;
int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF; PORTB = 0x00; // Init port B to 0s
	TimerSet(100);
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
			state = TWO;
			break;
		case TWO:
			state = THREE;
			break;
		case THREE:
			state = ONE;
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
		default:
			break;
	}
	
	
	
}



