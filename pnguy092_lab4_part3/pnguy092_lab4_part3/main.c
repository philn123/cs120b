/*
 * pnguy092_lab4_part3.c
 *
 * Created: 4/12/2019 4:12:48 PM
 * Author : Phillip
 */ 

#include <avr/io.h>
enum States{INIT, START, WAIT, HASH, UNLOCKED, LOCK} state;
    
void Tick();


int main(void)
{
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    state = INIT;
    while (1) 
    {
        Tick();
    }
}

void Tick(){
    switch(state){ //transitions
        case INIT:
            state = START;
            break;
        case START:
            if((PINA & 0x07) == 0x04){
                state = WAIT;
            }
            else if((PINA & 0x87) == 0x80){
                state = LOCK;
            }
            else{
                state = START;
            }
            break;
        case WAIT:
            if((PINA & 0x07) == 0x04){
                state = WAIT;
            }
            else if((PINA & 0x07) == 0x00){
                state = HASH;
            }
            else{
                state = START;
            }
            break;
        case HASH:
            if((PINA & 0x07) == 0x02){
                state = UNLOCKED;
            }
            else if((PINA & 0x87) == 0x80){
                state = LOCK;
            }
            else if((PINA & 0x07) == 0x01){
                state = START;
            }
            else{
                state = HASH;
            }
            break;
        case UNLOCKED:
            if((PINA & 0x80) == 0x80){
                state = LOCK;
            }
            else{
                state = UNLOCKED;
            }
            break;
        case LOCK:
            if((PINA & 0x87) == 0x80){ //if they keep holding then keep it here
                state = LOCK;
            }
            else{
                state = START;
            }
            break;
            
        default:
            break;
            
        
        
    }
    
    switch(state){ //actions
        case INIT:
            PORTC = 0x00;
            PORTB = 0x00;
            break;
        case START:
            PORTC = 0x01;
            PORTB = PORTB;
            break;
        case WAIT:
            PORTC = 0x02;
            PORTB = PORTB;
        case HASH:
            PORTC = 0x03;
            PORTB = PORTB;
        case UNLOCKED:
            PORTB = 0x01;
            PORTC = 0x04;
        case LOCK:
            PORTB = 0x05;
            PORTC = LOCK;
        default:
            break;
                
              
    }
  
}
