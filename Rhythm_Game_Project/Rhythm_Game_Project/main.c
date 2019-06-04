/*
 * Rhythm_Game_Project.c
 *
 * Created: 6/3/2019 10:12:22 PM
 * Author : Phillip
 */ 

#include <avr/io.h>
#include <avr/eeprom.h>
#include "io.c"
#include "scheduler.h"
#include "timer.h"
#include "Shift.h"

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
    LCD_Game_Menu();
    Shift_Init();
        
    Shift_transmit_data(255);
    Shift_transmit_data(0);
   
    
    while (1) 
    {
        for(unsigned char i = 0; i < 8; i++){
            Shift_transmit_data(128 >> i);
            delay_ms(500);
        }
    }        
    return 0;
}

