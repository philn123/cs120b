/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 10 Challenge 5
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned char TimerFlag = 0;
// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B; // bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s
	// AVR output compare register OCR1A.
	OCR1A = 125; // Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt
	//Initialize avr counter
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}
void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}
void TimerISR() {
	TimerFlag = 1;
}
// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
// Set TimerISR() to tick every M ms
void TimerSet( unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
unsigned char held_timer = 0x00;
enum Button_state{Raise,Lower,Wait_release,Init, Wait_input, Reset} b_state;
unsigned char frequency_dialer = 0x00;
void button_check();
void LED_update();
void main(){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	b_state = Init;
	unsigned char timer_period = 1;
	unsigned char button_counter = 200;
	TimerSet(timer_period);
	TimerOn();
	
	while(1){
		if(button_counter >= 30){
			button_check();
			button_counter = 0;
		}
		LED_update();
		while(!TimerFlag);
		TimerFlag = 0;
		button_counter += timer_period;
	}
}
void button_check(){
	switch(b_state){// state
		case Init:
		b_state = Wait_input;
		break;
		case Wait_input:
			if ((PINA & 0x02) == 0x00){
				b_state = Raise;
				held_timer = 0x00;
			}
			else if((PINA & 0x04) == 0x00){
				b_state = Lower;
				held_timer = 0x00;
			}
			else{
				b_state = Wait_input;
			}
			break;
		case Wait_release:
			if(((PINA & 0x02) == 0x00) && ((PINA & 0x04) ==0x00)){
				b_state = Reset;
			}
			else if((PINA & 0x02) == 0x00 ){
				held_timer ++;
				if(held_timer == 5){
					b_state = Raise;
				}
				else if(held_timer == 10){
					b_state = Raise;
				}
				else if(held_timer > 10){
					if(held_timer == 12){
						held_timer = 10;
						b_state = Raise;
					}
					else{
						b_state = Wait_release;
					}
				}
			}
			else if((PINA & 0x04) == 0x00 ){
				held_timer ++;
				if(held_timer == 5){
					b_state = Lower;
				}
				else if(held_timer == 10){
					b_state = Lower;
				}
				else if(held_timer > 10){
					if(held_timer == 12){
						held_timer = 10;
						b_state = Lower;
					}
					else{
						b_state = Wait_release;
					}
				}
			}
			else if((PINA & 0x02) == 0x00 || (PINA & 0x04) ==0x00){
				b_state = Wait_release;
			}
			else{
				b_state = Wait_input;
			}
			break;
		case Raise:
		b_state = Wait_release;
		break;
		case Lower:
		b_state = Wait_release;
		break;
		case Reset:
		b_state = Wait_release;
		break;
	}
	switch(b_state){//actions
		case Init:
		frequency_dialer = 0x00;
		break;
		case Wait_input:
		break;
		case Wait_release:
		break;
		case Raise:
		if(frequency_dialer == 9){
			break;
		}
		else{
			frequency_dialer++;
		}
		break;
		case Lower:
		if(frequency_dialer == 0x00){
			break;
		}
		else {
			frequency_dialer --;
		}
		break;
		case Reset:
		frequency_dialer = 0;
		break;
	}
}
void LED_update(){
	PORTB = frequency_dialer;
}