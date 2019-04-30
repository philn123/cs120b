/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 7 Exercise 1
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include "io.c"
#include <avr/interrupt.h>


volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char i = 0x00;

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



enum States{INIT, WAIT, INCREMENT, DECREMENT, WAIT2, RESET} state;
void Tick();


int main(void)
{
	/* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	state = INIT;
	TimerSet(50);
	TimerOn();
	LCD_init();
	
	while (1)
	{
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}

void Tick(){
	switch(state){ //transitions
		case INIT:
            LCD_Cursor(1);
            LCD_WriteData('O');
			state = WAIT;
			break;
		case WAIT:
			if((PINA & 0x03) == 0x03){
				state = RESET;
			}
			else if((PINA & 0x03) == 0x01){
				state = INCREMENT;
			}
			else if((PINA & 0x03) == 0x02){
				state = DECREMENT;
			}
			else{
				state = WAIT;
			}
			break;
		case INCREMENT:
			state = WAIT2;
			break;
		case DECREMENT:
			state = WAIT2;
			break;
		case WAIT2:
			if((PINA & 0x03) == 0x00){
				state = WAIT;
			}
			else if((PINA & 0x03) == 0x03){
				state = RESET;
			}
			else if((PINA & 0x03) == 0x01){
    			state = INCREMENT;
			}
            else if((PINA & 0x03) == 0x02){
                state = DECREMENT;
            }
			break;
		case RESET:
			if((PINA & 0x03) == 0x03){
				state = RESET;
			}
			else if((PINA & 0x02) == 0x02){
				state = RESET;
			}
			else if((PINA & 0x01) == 0x01){
				state = RESET;
			}
			else{
				state = INIT;
			}
			break;
		default:
			break;
		
	}
	switch(state){ //actions
		case INIT:
			break;
		case WAIT:
			break;
		case INCREMENT:
			if(i < 0x09){
				i++;
			}
			else{
				i = 9;
			}
            LCD_Cursor(1);
            LCD_WriteData(i + '0');
			break;
		case DECREMENT:
			if(i > 0){
				i--;
			}
			else{
				i = 0x00;
			}
            LCD_Cursor(1);
            LCD_WriteData(i + '0');
			break;
            
		case WAIT2:
			break;
		case RESET:
		    i = 0x00;
            LCD_Cursor(1);
            LCD_WriteData(i + '0');
			break;
		default:
			break;
		

	}



}
