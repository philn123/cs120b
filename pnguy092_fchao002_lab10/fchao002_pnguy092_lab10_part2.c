/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 10 Exercise 2
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

void ThreeLed();
void BlinkingLed();
void CombineLed();

unsigned char three_leds = 0x00;
unsigned char blinking_led = 0x00;

enum ThreeLEDs{TStart, TGo} state3;
enum BlinkLEDs{BStart, Blink} blink_state;



int main(void)
{
    /* Replace with your application code */
    DDRB = 0xFF; PORTB = 0x00;
    const unsigned char timer_period = 10;
    TimerSet(timer_period);
    TimerOn();
    unsigned char three_time = 3;
    unsigned char blink_time = 100;
    
    while (1)
    {
        
        if(three_time >= 30){
            ThreeLed();
            three_time = 0;
        }
        if(blink_time >= 100){
            BlinkingLed();
            blink_time = 0;
        }
        CombineLed();
        while(!TimerFlag);
        TimerFlag = 0;
        three_time += timer_period;
        blink_time += timer_period;
        
    }
}

void ThreeLed(){
    switch(state3){
        case TStart:
        state3 = TGo;
        break;
        case TGo:
        state3 = TGo;
        break;
        default:
        break;
    }
    switch(state3){
        case TStart:
        break;
        case TGo:
        if(three_leds == 0x04){
            three_leds = 0x01;
        }
        else if(three_leds == 0x00){
            three_leds = 0x01;
        }
        else{
            three_leds = three_leds << 1;
        }
        break;
        default:
        break;
        
    }
    
    
}
void BlinkingLed(){
    switch(blink_state){
        case BStart:
        blink_state = Blink;
        break;
        case Blink:
        blink_state = Blink;
        break;
        default:
        break;
    }
    switch(blink_state){
        case BStart:
        break;
        case Blink:
        if(blinking_led == 0x00){
            blinking_led = 0x08;
            break;
        }
        else{
            blinking_led = 0x00;
        }
        break;
        default:
        break;
    }
}
void CombineLed(){
    PORTB = blinking_led | three_leds;
}