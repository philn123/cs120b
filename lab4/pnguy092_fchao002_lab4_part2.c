/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 4 Exercise 2
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
enum States{INIT, WAIT, INCREMENT, DECREMENT, WAIT2, RESET} state;
void Tick();


int main(void)
{
    /* Replace with your application code */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x07;
    state = INIT;
    while (1) 
    {
        Tick();
    }
}

void Tick(){
    switch(state){ //transitions
        case INIT:
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
            else{
                state = WAIT2;
            }
            break;
        case RESET:
            if((PINA & 0x03) == 0x03 || 0x02 || 0x01){
                state = RESET;
            }
            else{
                state = WAIT;
            }
            break;
        default:
           break;
    }
    switch(state){ //actions
        case INIT:
            PORTC = 0x07;
            break;
        case WAIT:
            PORTC = PORTC;
            break;
        case INCREMENT:
            if(PORTC < 0x09){
                PORTC = PORTC + 1;
            }
            else{
                PORTC = 0x09;
            }
            break;
        case DECREMENT:
            if(PORTC > 0){
                PORTC = PORTC - 1;
            }
            else{
                PORTC = 0x00;
            }
            break;
        case WAIT2:
            PORTC = PORTC;
            break;
        case RESET:
            PORTC = 0x00;
            break;
        default:
            break;

    }



}
