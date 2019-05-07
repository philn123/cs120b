/*
 * pnguy092_lab9_part2.c
 *
 * Created: 5/5/2019 4:11:32 PM
 * Author : Phillip
 */ 

#include <avr/io.h>

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
void Tick();
enum States{Start, Init, Up, Down, Toggle, Wait} state;
double array[9] = {0,261.33,293.66,329.63,349.23,392.00,440.00,493.88,523.25};
unsigned char temp = 0;
unsigned char position = 0;

int main(void)
{
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    state = Start;
    PWM_on();
    temp = 1; //means sound is on
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
                state = Up;
            }
            else if((PINA & 0x07) == 0x02){
                state = Down;
            }
            else if((PINA & 0x07) == 0x04){
                state = Toggle;
            }
            else{
                state = Init;
            }
            break;
        case Up:
            state = Wait;
            break;
        case Down:
            state = Wait;
            break;
        case Toggle:
            state = Wait;
            break;
        case Wait:
            if((PINA & 0x07) != 0x00){
                state = Wait;
            }
            else{
                state = Init;
            }
            break;
        default:
            break;
        
    }
    
    switch(state){
        case Start:
            break;
        case Init:
            break;
        case Up:
            if(position < 8){
                position++;
            }
            else{
                position = 8;
            }
            break;
        case Down:
            if(position > 1){
                position--;
            }
            else{
                position = 1;
            }
            break;
        case Toggle:
            if(temp){
                PWM_off();
                temp = 0;
            }
            else{
                PWM_on();
                temp = 1;
            }
        case Wait:
            set_PWM(array[position]);
            break;
        default:
            break;
    }
    
    
    
    
}

