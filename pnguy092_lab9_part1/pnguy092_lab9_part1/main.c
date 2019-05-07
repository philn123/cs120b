/*
 * pnguy092_lab9_part1.c
 *
 * Created: 5/5/2019 2:16:38 PM
 * Author : Phillip
 */ 

#include <avr/io.h>

void Tick();
enum States{Start, Init, On, Off} state;
    
// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
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


int main(void)
{
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x0FF; PORTB = 0x00;
    PWM_on();
    state = Start;
    while (1) 
    {
        Tick();
    }
}

void Tick(){
    switch(state){
        case Start:
            state = Init;
            break;
        case Init:
            if((PINA & 0x07) == 0x01){
                state = On;
            }
            else if((PINA & 0x07) == 0x02){
                state = On;
            }
            else if((PINA & 0x07) == 0x04){
                state = On;
            }
            else{
                state = Init;
            }
            break;
        case On:
            if((PINA & 0x07) == 0x01){
                state = On;
            }
            else if((PINA & 0x07) == 0x02){
                state = On;
            }
            else if((PINA & 0x07) == 0x04){
                state = On;
            }
            else if((PINA & 0x07) == 0x00){
                state = Off;
            }
            else if((PINA & 0x07) == 0x03){
                state = Off;
            }
            else if((PINA & 0x07) == 0x05){
                state = Off;
            }
            else if((PINA & 0x07) == 0x07){
                state = Off;
            }
            else if((PINA & 0x07) == 0x06){
                state = Off;
            }
            break;
        
        case Off:             
            state = Init;
            break;
        default:
            break;
       
    }
    switch(state){
        case Start:
            break;
        case Init:
            set_PWM(0);
            break;
        case On:
            if((PINA & 0x07) == 0x01){
                set_PWM(261.33);
            }
            else if((PINA & 0x07) == 0x02){
                set_PWM(293.66);
            }
            else if((PINA & 0x07) == 0x04){
                set_PWM(329.63);
            }
            break;
        case Off:
            set_PWM(0);
            break;
        default:
            break;
        
    }
    
    
}

