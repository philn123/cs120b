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
    
    
    
    while (1) 
    {
    }
}

