/*
 * pnguy092_project.c
 *
 * Created: 5/21/2019 8:36:34 AM
 * Author : Phillip
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include "io.h"
#include "io.c"
#include "scheduler.h"
#include "timer.h"
#include "shift.h"

enum Menu{Menu_Init, Menu_Start, Menu_Score} state;
enum RGB_Matrix{RGB_INIT, RGB_Test} state2;
unsigned char menu_introduction[] = "Rhythm Game";
unsigned char pic[] = {0,36,36,36,0,66,60,0};
unsigned char score = 0;

void Menu_Tick(){
    switch(state){
        case Menu_Init:
            state = Menu_Start;
            break;
        case Menu_Start:
            state = Menu_Score;
            break;
        case Menu_Score:
            state = Menu_Start;
            break;
        default:
            break;
    }
    
    switch(state){
        case Menu_Init:
            break;
        case Menu_Start:
           
            LCD_Cursor(17);
            for(unsigned char i = 0; i < 11; i++){
                LCD_WriteData(menu_introduction[i]);
            }
            break;
        case Menu_Score:
                LCD_ClearScreen();
                LCD_Cursor(1);
                LCD_WriteData(score + '0');
                score += 1;
                eeprom_update_byte((uint8_t*) 4, (uint8_t) score);
            break;
    }
    
    
    
}

/*
void RGB_Matrix_Tick(){
    switch(state2){
        case RGB_INIT:
            state2 = RGB_Test;
            break;
        case RGB_Test:
            state2 = RGB_Test;
            break;
    }
    switch(state2){
        case RGB_INIT:
            break;
        case RGB_Test:
            for(unsigned i = 0; i < 8; i++){
                Shift_transmit_data(pic[i]);
                Shift_transmit_data(255 >> i);
            }
            
    }
}

*/

int main(void)
{
    /* Replace with your application code */
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
 
 
    TimerSet(100);
    TimerOn();
    LCD_init();
  
    score = eeprom_read_byte((uint8_t*) 4);
    Shift_transmit_data(0);
    Shift_transmit_data(255);
    unsigned char row = 1;
    while (1) 
    {
        Menu_Tick();
        //RGB_Matrix_Tick();
        
        for(unsigned i = 0; i < 8; i++){
           
            Shift_transmit_data(128 >> i);
            Shift_transmit_data(~row);
            
            if(i == 7){
                row++;
            }
            
           
        }
        
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

