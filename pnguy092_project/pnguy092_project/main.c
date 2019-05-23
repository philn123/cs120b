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


enum Menu{Menu_Init, Menu_Start, Menu_Score} state;
unsigned char menu_introduction[] = "Rhythm Game";

unsigned char score = 0;
//custom characters
/*
unsigned char customChar[8] = { //left arrow
        0b10000,
        0b01000,
        0b00100,
        0b00010,
        0b00010,
        0b00100,
        0b01000,
        0b10000
};
unsigned char customChar2[8] = { //right arrow
    0b00001,
    0b00010,
    0b00100,
    0b01000,
    0b00100,
    0b00010,
    0b00001,
    0b00000
};
unsigned char customChar3[8] = { //down arrow
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b01110,
    0b00100
};
unsigned char customChar4[8] = { //up arrow
    0b00100,
    0b01110,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100
};
*/
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




int main(void)
{
    /* Replace with your application code */
    DDRA = 0xFF; PORTA = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
 
 
    TimerSet(2000);
    TimerOn();
    LCD_init();
  
    score = eeprom_read_byte((uint8_t*) 4);

    while (1) 
    {
        Menu_Tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
}

