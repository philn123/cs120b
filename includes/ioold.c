#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "io.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))
          
/*-------------------------------------------------------------------------*/

#define DATA_BUS PORTD	// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTC	// port connected to pins 4 and 6 of LCD disp.
#define RS 0			// pin number of uC connected to pin 4 of LCD disp.
#define E 1 // pin number of uC connected to pin 6 of LCD disp.

/*-------------------------------------------------------------------------*/
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


void LCD_ClearScreen(void) {
   LCD_WriteCommand(0x01);
}



void LCD_WriteCommand (unsigned char Command) {
   CLR_BIT(CONTROL_BUS,RS);
   DATA_BUS = Command;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
   SET_BIT(CONTROL_BUS,RS);
   DATA_BUS = Data;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(1);
}

void LCD_DisplayString( unsigned char column, const unsigned char* string) {
   LCD_ClearScreen();
   unsigned char c = column;
   while(*string) {
      LCD_Cursor(c++);
      LCD_WriteData(*string++);
   }
}

void LCD_Cursor(unsigned char column) {
   if ( column < 17 ) { // 16x1 LCD: column < 9
						// 16x2 LCD: column < 17
      LCD_WriteCommand(0x80 + column - 1);
   } else {
      LCD_WriteCommand(0xB8 + column - 9);	// 16x1 LCD: column - 1
											// 16x2 LCD: column - 9
   }
}

void delay_ms(int miliSec) //for 8 Mhz crystal

{
    int i,j;
    for(i=0;i<miliSec;i++)
    for(j=0;j<775;j++)
  {
   asm("nop");
  }
}

void LCD_Custom_Character (unsigned char loc, unsigned char *msg)
{
    unsigned char i;
    if(loc<8)
    {
     LCD_WriteCommand (0x40 + (loc*8));  /* Command 0x40 and onwards forces 
                                       the device to point CGRAM address */
       for(i=0;i<8;i++){  /* Write 8 byte for generation of 1 character */
           LCD_WriteData(msg[i]);  
       }           
    }   
}

void LCD_init(void) {

    //wait for 100 ms.
    delay_ms(100);
    LCD_WriteCommand(0x38);
    LCD_WriteCommand(0x06);
    LCD_WriteCommand(0x0f);
    LCD_WriteCommand(0x01);
    delay_ms(10);
    
    
    LCD_Cursor(6);
    LCD_Custom_Character(0,customChar);
    LCD_Custom_Character(1, customChar4);
    LCD_Custom_Character(2, customChar3);
    LCD_Custom_Character(4, customChar2);
    LCD_WriteCommand(0x0C);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x02);
    LCD_WriteData(0x04);
    
    
}
