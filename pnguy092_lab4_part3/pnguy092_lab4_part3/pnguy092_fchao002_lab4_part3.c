/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 4 Exercise 3
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
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
            else if((PINA & 0x07) == 0x01){ //if they hit x
                state = START;
            }
			else if((PINA & 0x07) == 0x03){ //if they hit x & y
				state = START;
			}
			else if((PINA & 0x07) == 0x07){ //if they hit all 3
				state = START;
			}
            else{
                state = HASH;
            }
            break;
        case UNLOCKED:
            if((PINA & 0x87) == 0x80){
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
            else if((PINA & 0x07) == 0x01){
	            state = LOCK;
            }
            else if((PINA & 0x07) == 0x02){
	            state = LOCK;
            }
            else if((PINA & 0x07) == 0x04){
	            state = LOCK;
            }
            else if((PINA & 0x07) == 0x07){
	            state = LOCK;
            }
            else if((PINA & 0x07) == 0x87){
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
			break;
        case HASH:
            PORTC = 0x03;
            PORTB = PORTB;
			break;
        case UNLOCKED:
            PORTB = 0x01;
            PORTC = 0x04;
			break;
        case LOCK:
            PORTB = 0x00;
            PORTC = LOCK;
			break;
        default:
            break;
                
              
    }
  
}
