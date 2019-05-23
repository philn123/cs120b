/* Partner 1 Name & E-mail: Phillip Nguyen & pnguy092@ucr.edu
* Partner 2 Name & E-mail: Fangsheng Chao & fchao002@ucr.edu
* Lab Section: 023
* Assignment: Lab 11 Exercise 3
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
#include "keypad.h"

enum States{SM1_out};
unsigned char tmpB = 0x00;

int SM1Tick(int state){
    unsigned char x;
    x = GetKeypadKey();
    switch(state){
        case SM1_out:
        switch(x){
            case '\0': tmpB = 0x1F; break; // All 5 LEDs on
            case '1': tmpB = 0x01;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break; // hex equivalent
            case '2': tmpB = 0x02;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '3': tmpB = 0x03;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '4': tmpB = 0x04;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '5': tmpB = 0x05;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '6': tmpB = 0x06;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '7': tmpB = 0x07;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '8': tmpB = 0x08;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '9': tmpB = 0x09;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case 'A': tmpB = 0x0A;
            LCD_Cursor(1); LCD_WriteData(tmpB + 0x37); break;
            case 'B': tmpB = 0x0B;
            LCD_Cursor(1); LCD_WriteData(tmpB + 0x37); break;
            case 'C': tmpB = 0x0C;
            LCD_Cursor(1); LCD_WriteData(tmpB + 0x37); break;
            case 'D': tmpB = 0x0D;
            LCD_Cursor(1); LCD_WriteData(tmpB + 0x37); break;
            case '*': tmpB = 0x0E;
            LCD_Cursor(1); LCD_WriteData(tmpB + 0x1C); break;
            case '0': tmpB = 0x00;
            LCD_Cursor(1); LCD_WriteData(tmpB + '0'); break;
            case '#': tmpB = 0x0F;
            LCD_Cursor(1); LCD_WriteData(tmpB + 0x14); break;
            default: tmpB = 0x1B; break; // Should never occur. Middle LED off.
        }
        PORTB = tmpB;
        state = SM1_out;
        break;
    }
    return state;
    
    
}

int main()
{
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
    DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
    unsigned long int SM1Tick_calc = 1;
    unsigned long int tempGCD = 1;
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
    
    return 0;
}

