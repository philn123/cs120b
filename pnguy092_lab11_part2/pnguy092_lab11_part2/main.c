/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 11 Exercise 2
*
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <avr/io.h>
#include "timer.h"
#include "io.h"
#include "io.c"
#include "scheduler.h"


unsigned char cnt = 0;
enum States{SM1_out};
const unsigned char sentence[61] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s', ' ', 'L','E','G','E','N','D','.','.','.', ' ','w','a','i','t',' ','f'
,'o', 'r', ' ', 'i', 't', ' ', 'D', 'A', 'R', 'Y','!', ' ',' ',' ',' ',' ',' ',' ',' ',' '};
int SM1Tick(int state){
    switch(state){
        case SM1_out:
        for(int j = 1; j <= 16; j++){
            LCD_Cursor(j);
            LCD_WriteData(sentence[cnt + j]);
            if(cnt+j == 61){
                cnt = 0;
            }
            
        }
        cnt++;
        break;
        
        
    }
    return state;
}

int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
    DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
    
    unsigned long int SM1Tick_calc = 10;
    unsigned long int tempGCD = 10;
    unsigned long int GCD = tempGCD;
    unsigned long int SM1Tick_period = SM1Tick_calc;
    
    static task task1;
    task *tasks[] = {&task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    
    task1.state = 0;
    task1.period = SM1Tick_period;
    task1.elapsedTime = SM1Tick_period;
    task1.TickFct = &SM1Tick;
    
    
    /* Replace with your application code */
    TimerSet(GCD);
    TimerOn();
    LCD_init();
    LCD_ClearScreen();
    unsigned short i; // Scheduler for-loop iterator
    
    while(1) {
        // Scheduler code
        for ( i = 0; i < numTasks; i++ ) {
            // Task is ready to tick
            if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
                // Setting next state for task
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                // Reset the elapsed time for next tick.
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
        }
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

