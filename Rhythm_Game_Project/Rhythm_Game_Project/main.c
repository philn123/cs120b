/*
 * Rhythm_Game_Project.c
 *
 * Created: 6/3/2019 10:12:22 PM
 * Author : Phillip
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include "io.c"
#include "timer.h"
#include "scheduler.h"
#include "Shift.h"

//DEFINES
#define LEFT_BUTTON (PINA & 0x08)
#define DOWN_BUTTON (PINA & 0x04)
#define UP_BUTTON  (PINA & 0x02)
#define RIGHT_BUTTON (PINA & 0x01)

//Buttons
bool LEFT = false;
bool RIGHT = false;
bool UP = false;
bool DOWN = false;

//TYPES
enum LFT{LFT_INIT, LFT_WAIT};
enum RGHT{RGHT_INIT, RGHT_WAIT};
enum UPP{UP_INIT, UP_WAIT};
enum DOWNN{DOWN_INIT, DOWN_WAIT};
enum LCD_Menu {LCD_Menu_Init, LCD_Menu_Start, LCD_Menu_Songs};
enum RGB_Matrix{RGB_INIT, RGB_MENU};
    
//Tick Functions
int Left_Tick(int state);
int Right_Tick(int state);
int Up_Tick(int state);
int Down_Tick(int state);
int LCD_Menu_Tick(int state);
int RGB_Matrix_Tick(int state);
//tasks
const unsigned long tasksPeriodGCD = 5;
const unsigned char tasksNum = 6;
task tasks[6];

//global variables
//unsigned char pic[8] = {4, 12, 24, 24, 24, 24, 12, 4};
unsigned char pic[8] = {3, 0, 0, 0, 0, 0, 0, 0};
int main(void)
{
    //LCD PORTS & RGB MATRIX
    DDRD = 0xFF; PORTD = 0x00;
    DDRC = 0XFF; PORTC = 0x00; //0 & 1 are LCD Control Lines, 2,3,4 are RGB PORTS
    
    //BUTTON INPUT PORTS
    DDRA = 0x00; PORTA = 0xFF;
    
    //BUZZER PORT
    DDRB = 0x0FF; PORTB = 0x00; //PB6 is buzzer
    
    //Initialize LCD and Matrix
    LCD_init();
    
    Shift_Init();   
    Shift_transmit_data(0);
    Shift_transmit_data(255);
    
    //Task Code
    unsigned char tasks_increment = 0;
    
    tasks[tasks_increment].state = LFT_INIT;
    tasks[tasks_increment].period = 30;
    tasks[tasks_increment].elapsedTime = tasks[tasks_increment].period;
    tasks[tasks_increment].TickFct = &Left_Tick;
    
    tasks_increment++;
    
    tasks[tasks_increment].state = RGHT_INIT;
    tasks[tasks_increment].period = 30;
    tasks[tasks_increment].elapsedTime = tasks[tasks_increment].period;
    tasks[tasks_increment].TickFct = &Right_Tick;
    
    tasks_increment++;
    
    tasks[tasks_increment].state = UP_INIT;
    tasks[tasks_increment].period = 30;
    tasks[tasks_increment].elapsedTime = tasks[tasks_increment].period;
    tasks[tasks_increment].TickFct = &Up_Tick;
    
    
    tasks_increment++;
    
    tasks[tasks_increment].state = DOWN_INIT;
    tasks[tasks_increment].period = 30;
    tasks[tasks_increment].elapsedTime = tasks[tasks_increment].period;
    tasks[tasks_increment].TickFct = &Down_Tick;
    
    
    tasks_increment++;
    
    tasks[tasks_increment].state = RGB_INIT;
    tasks[tasks_increment].period = 10;
    tasks[tasks_increment].elapsedTime = tasks[tasks_increment].period;
    tasks[tasks_increment].TickFct = &RGB_Matrix_Tick;
    
    
    tasks_increment++;
    
    tasks[tasks_increment].state = LCD_Menu_Init;
    tasks[tasks_increment].period = 50;
    tasks[tasks_increment].elapsedTime = tasks[tasks_increment].period;
    tasks[tasks_increment].TickFct = &LCD_Menu_Tick;
    
    //Timer
    TimerSet(tasksPeriodGCD);
    TimerOn();
    
    
    while (1) 
    {
        sleep_mode();
    }        
    return 0;
}

int Left_Tick(int state){
    switch(state){
        case LFT_INIT:
            state = LFT_WAIT;
            break;
        case LFT_WAIT:
            state = LFT_WAIT;
            break;
    }
    switch(state){
        case LFT_INIT:
            break;
        case LFT_WAIT:
            if(LEFT_BUTTON == 0x00){
                LEFT = true;
                break;
            }
            else{
                LEFT = false;
                break;
            }
    }
    
    return state;
}

int Right_Tick(int state){
    switch(state){
        case RGHT_INIT:
            state = RGHT_WAIT;
            break;
        case RGHT_WAIT:
            state = RGHT_WAIT;
            break;
    }
    switch(state){
        case RGHT_INIT:
            break;
        case RGHT_WAIT:
            if(RIGHT_BUTTON == 0x00){
                RIGHT = true;
                break;
            }
            else{
                RIGHT = false;
                break;
            }
    }
    
    return state;
}

int Up_Tick(int state){
    switch(state){
        case UP_INIT:
            state = UP_WAIT;
            break;
        case UP_WAIT:
            state = UP_WAIT;
            break;
    }
    switch(state){
        case UP_INIT:
            break;
        case UP_WAIT:
            if(UP_BUTTON == 0x00){
                UP = true;
                break;
            }
            else{
                UP = false;
                break;
            }
    }
    
    return state;
}

int Down_Tick(int state){
    switch(state){
        case DOWN_INIT:
            state = DOWN_WAIT;
            break;
        case DOWN_WAIT:
            state = DOWN_WAIT;
            break;
    }
    switch(state){
        case DOWN_INIT:
            break;
        case DOWN_WAIT:
            if(DOWN_BUTTON == 0x00){
                DOWN = true;
                break;
            }
            else{
                DOWN = false;
                break;
            }
    }
    
    return state;
}

int LCD_Menu_Tick(int state){
    static unsigned char current_song_choice = 0;
    switch(state){ //transitions
        case LCD_Menu_Init:
            state = LCD_Menu_Start;
            break;
        case LCD_Menu_Start:
            if(LEFT && RIGHT && DOWN && UP){
                LCD_ClearScreen();
                current_song_choice = 0;
                state = LCD_Menu_Songs;
                break;
            }
            else{
                state = LCD_Menu_Start;
                break;
            }
        case LCD_Menu_Songs:
            if(LEFT && !RIGHT && !UP && !DOWN){
                LCD_ClearScreen();
                state = LCD_Menu_Start;
                break;
            }
            else if(DOWN && !UP && !LEFT && !RIGHT){
                if(current_song_choice){
                    current_song_choice = 1;
                }
                else{
                    current_song_choice += 1;
                }
                break;
            }
            else if(!DOWN && UP && !LEFT && !RIGHT){
                if(!current_song_choice){
                    current_song_choice = 0;
                }
                else{
                current_song_choice -= 1;
                
                }            
                break;
            }
            else{
                state = LCD_Menu_Songs;
                break;
            }               
    }
    switch(state){ //actions
        case LCD_Menu_Init:
            break;
        case LCD_Menu_Start:
            LCD_Game_Menu();
            break;
        case LCD_Menu_Songs:
            if(current_song_choice){
                LCD_Cursor(1);
                LCD_WriteData(' ');
                LCD_Cursor(17);
            }
            else{
                LCD_Cursor(17);
                LCD_WriteData(' ');
                LCD_Cursor(1);
            }
            LCD_WriteData(0xA5);
            LCD_Write_Single_Line(2,1, "ZEN ZEN ZENSE");
            LCD_Write_Single_Line(2,2, "NO");
            break;
        
        
    }

    return state;
}

int RGB_Matrix_Tick(int state){
    switch(state){
        case RGB_INIT:
            state = RGB_MENU;
            break;
        case RGB_MENU:
            state = RGB_MENU;
            break;
    }
    switch(state){
        case RGB_INIT:
            break;
        case RGB_MENU:
            /*if(LEFT || RIGHT || UP || DOWN){
                for(unsigned char i = 0; i < 8; i++){
                    Shift_transmit_data(128 >> i);
                    Shift_transmit_data(~pic[i]);
                    delay_ms(1);
                }
            }
            Shift_transmit_data(0);
            Shift_transmit_data(0);
            */
            for(unsigned char i = 0; i < 8; i++){
                Shift_transmit_data(128 >> i);
                Shift_transmit_data(~pic[i]);
                delay_ms(5);
            }
            for(unsigned char k = 0; k < 8; k++){
                pic[k] <<= 1;
            }
            break;
    }
    
    return state;
}