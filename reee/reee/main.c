/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 9 Challenge
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

/*
const double c3 = 130.812; 
const double cs3 = 138.591; 
const double d3 = 146.832; const double ds3 = 155.563; const double e3 = 164.813; const double f3 = 174.614; const double fs3 = 184.997;
const double g3 = 195.997; const double gs3 = 207.652; const double a3 = 220; const double as3 = 233.081; const double b3 = 246.941;
const double c4 = 261.625; const double cs4 = 277.182; const double d4 = 293.664; const double ds4 = 311.126; const double e4 = 329.627; const double f4 = 349.228; const double fs4 = 369.994;
const double g4 = 391.995; const double gs4 = 415.304;
*/






/*const double notes[36] = {e4, b3, e4, b3, cs4, ds4, gs3, gs3, cs4, b3, a3, b3, ds3,
ds3, f3, f3, g3, gs3, gs3, as3, c4, d4, ds4, f4,as3,g4,f4,ds4,f4,d4,as3,as3,ds4,d4,c4,d4};
*/
/*const double notes[36] = {329.627, 246.941,329.627, 246.941, 277.182, 311.126, 207.652, 207.652, 277.182, 246.941,220,
     246.941, 155.563, 155.563, 174.614, 174.614, 195.997, 207.652, 207.652, 261.625, }
     
*/
const double notes[36] = {329.627, 246.941, 329.627, 246.941, 277.182, 311.126, 207.652,207.652, 277.182, 246.941, 220, 246.941, 155.563,
155.563, 174.614, 174.614, 195.997, 207.652, 207.652, 233.081, 261.625, 293.664, 311.126, 349.228,233.081, 391.995,349.228,311.126,349.228,293.664,233.081,233.081,311.126,293.664,261.625,293.664};
double timing[36]={14,2,4,3,1,4,3,/*checkpoint 1*/ 1,4,3,1,4,2 /*checkpoint 2*/,2,4,2,2,4,2,2,4,2,2,6,/*checkpoint 3*/2,4,3,1,4,2,2,4,4,3,1,4};
unsigned char position = 0;
volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.
unsigned char finished = 0;

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
void Tick();
void Play();
void TimerOn() {
    // AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
    // bit2bit1bit0=011: pre-scaler /64
    // 00001011: 0x0B
    // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
    // Thus, TCNT1 register will count at 125,000 ticks/s

    // AVR output compare register OCR1A.
    OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
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
void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}


void set_PWM(double frequency) {
    
    
    // Keeps track of the currently set frequency
    // Will only update the registers when the frequency
    // changes, plays music uninterrupted.
    static double current_frequency;
    if (frequency != current_frequency) {

        if (!frequency) TCCR3B &= 0x08; //stops timer/counter
        else TCCR3B |= 0x03; // resumes/continues timer/counter
        
        // prevents OCR3A from overflowing, using prescaler 64
        // 0.954 is smallest frequency that will not result in overflow
        if (frequency < 0.954) OCR3A = 0xFFFF;
        
        // prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250) OCR3A = 0x0000;
        
        // set OCR3A based on desired frequency
        else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

        TCNT3 = 0; // resets counter
        current_frequency = frequency;
    }
}
void PWM_on() {
    TCCR3A = (1 << COM3A0);
    // COM3A0: Toggle PB6 on compare match between counter and OCR3A
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    // WGM32: When counter (TCNT3) matches OCR3A, reset counter
    // CS31 & CS30: Set a prescaler of 64
    set_PWM(0);
}
void PWM_off() {
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}
enum States{Start, Init, On, Off} state;


int main(void)
{
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    PWM_on();
    state = Start;
    while (1)
    {
        Tick();
    }
}

void Tick(){
    switch(state){//states
        case Start:
            state = Init;
            break;
        case Init:
            if((PINA & 0x07) == 0x01){
                state = On;
            }
            else{
                state = Init;
            }
            break;
        case On:
            state = Init;
        break;
        
        case Off:
            state = Init;
            break;
        default:
            break;
        
    }
    switch(state){//actions
        case Start:
            break;
        case Init:
            break;
        case On:
        
        Play();
        break;
        case Off:
        set_PWM(0);
        break;
        default:
        break;
        
    }
    
    
}

void Play(){
    
    while(position < 36){
        TimerSet(timing[position]*24);
        TimerOn();
        set_PWM(notes[position]);
        while(!TimerFlag);
        TimerFlag = 0;
        position++;
        TimerOff();
    }
    set_PWM(0);
    position = 0;
}


