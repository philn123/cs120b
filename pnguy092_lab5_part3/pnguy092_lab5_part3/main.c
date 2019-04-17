/*
 * pnguy092_lab5_part3.c
 *
 * Created: 4/16/2019 9:04:21 AM
 * Author : Phillip
 */ 

#include <avr/io.h>
enum States{INIT, START, WAIT, ONE, FIRST, SECOND, WAIT2} state;
void Tick();


int main(void)
{
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    while (1) 
    {
        Tick();
    }
}
void Tick(){
    switch(state){
        case INIT:
            state = START;
            break;
        case START:
            if((PINA & 0x01) == 0x01){
                state = ONE;
            }
            else{
                state = START;
            }
            break;
        case WAIT:
            if((PINA & 0x01) == 0x01){
                state = WAIT;
            }
            else{
                state = FIRST;
            }
            break;
        case ONE:
            if((PINA & 0x01) == 0x00){
                state = WAIT;
            }
            else{
                state = ONE;
            }
            break;
        case FIRST:
            if(PORTC < 63 && (PINA & 0x01) == 0x01){
                PORTC = PORTC * 2;
                state = WAIT;
            }
            else if(PORTC >= 63 && (PINA & 0x01) == 0x01){
                state = SECOND;
            }
            else{
                state = FIRST;
            }
            break;
        case SECOND:
            if(PORTC > 0 && (PINA & 0x01) == 0x01){
                PORTC = PORTC / 2;
                state = WAIT2;
            }
            else if(PORTC == 0 && (PINA & 0x01) == 0x01){
                state = INIT;
            }
            else{
                state = SECOND;
            }
            break;
        case WAIT2:
            if((PINA & 0x01) == 0x01){
                state = WAIT2;
                
            }
            else{
                state = SECOND;
            }
            break;
        default:
            break;
    }
    
    switch(state){
        case INIT:
            break;
        case START:
            PORTC = 0x00;
            break;
        case WAIT:
            PORTC = PORTC;
            break;
        case ONE:
            PORTC = 1;
            break;
        case FIRST:
            break;
        case SECOND:
            break;
        case WAIT2:
            PORTC = PORTC;
            break;
        default:
            break;
    }
    
    
}
