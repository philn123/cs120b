/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 10 Challenge 4
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

void ThreeLed();
void BlinkingLed();
void CombineLed();
void Buzzer();
void button_check();
unsigned char three_leds = 0x00;
unsigned char blinking_led = 0x00;
enum ThreeLEDs{TStart, TGo} state3;
enum BlinkLEDs{BStart, Blink} blink_state;
enum Speaker{SStart, Sound, Sound_off, Sound_wait} sound;
enum Button_state{Raise,Lower,Wait_release,Init, Wait_input} b_state;
unsigned char frequency_dialer = 0x02;

void main(){
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    
    unsigned char timer_period = 1;
    TimerSet(timer_period);
    TimerOn();
    unsigned char three_time = 30;
    unsigned char blink_time = 100;
    unsigned char speaker_time = 2;
    b_state = Init;
    //PWM_on();
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
        if(speaker_time >= frequency_dialer){
            Buzzer();
            speaker_time = 0;
        }
        button_check();
        CombineLed();
        while(!TimerFlag);
        TimerFlag = 0;
        three_time += timer_period;
        blink_time += timer_period;
        speaker_time += timer_period;
        
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
        }
        else if((PINA & 0x04) == 0x00){
            b_state = Lower;
        }
        else{
            b_state = Wait_input;
        }
        break;
        case Wait_release:
        if((PINA & 0x02) == 0x00 || (PINA & 0x04) ==0x00){
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
    }
    switch(b_state){//actions
        case Init:
        frequency_dialer = 0x02;
        break;
        case Wait_input:
        break;
        case Wait_release:
        break;
        case Raise:
        if(frequency_dialer == 0x01){
            break;
        }
        else{
            frequency_dialer--;
        }
        break;
        case Lower:
        if(frequency_dialer == 0x05){
            break;
        }
        else {
            frequency_dialer ++;
        }
        break;
    }
}
void Buzzer(){
    switch(sound){
        case SStart:
        sound = Sound_wait;
        break;
        case Sound:
        if((PINA & 0x01) == 0x00){
            sound = Sound_off;
        }
        else{
            sound = Sound_wait;
        }
        break;
        case Sound_off:
        if((PINA & 0x01) == 0x00){
            sound = Sound;
        }
        else{
            sound = Sound_wait;
        }
        break;
        case Sound_wait:
        if((PINA & 0x01) == 0x00){
            sound = Sound;
        }
        else{
            sound = Sound_wait;
        }
        break;
        
    }
    switch(sound){
        case SStart:
        break;
        case Sound:
        PORTB = PORTB | 0x10;
        break;
        case Sound_off:
        PORTB = PORTB & 0xEF;
        break;
        case Sound_wait:
        PORTB = PORTB & 0xEF;
        break;
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
