
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "delay_x.h"


typedef struct 
{ 
  unsigned char bit0:1; 
  unsigned char bit1:1; 
  unsigned char bit2:1; 
  unsigned char bit3:1; 
  unsigned char bit4:1; 
  unsigned char bit5:1; 
  unsigned char bit6:1; 
  unsigned char bit7:1; 
}io_reg; 

#define LCD_RS    0x20//  ((volatile io_reg*)_SFR_MEM_ADDR(PORTD))->bit7

#define LCD_EN     0x80 //((volatile io_reg*)_SFR_MEM_ADDR(PORTD))->bit6 

//#define LCD_data_bit_7 ((volatile io_reg*)_SFR_MEM_ADDR(PORTD))->bit7

//#define LCD_data_bit_6 ((volatile io_reg*)_SFR_MEM_ADDR(PORTD))->bit6

//#define LCD_data_bit_5 ((volatile io_reg*)_SFR_MEM_ADDR(PORTD))->bit5

//#define LCD_data_bit_4 ((volatile io_reg*)_SFR_MEM_ADDR(PORTD))->bit4
void lcd_instr(char cmd)
{
 _delay_ms(20);
	PORTD = ((cmd >> 4) & 0x0F)|LCD_EN;
	 _delay_ms(20);
        PORTD = ((cmd >> 4) & 0x0F);

        PORTD = (cmd & 0x0F)|LCD_EN;
		 _delay_ms(20);
        PORTD = (cmd & 0x0F);

        _delay_ms(200);
        _delay_ms(200);
/*
	LCD_EN=1;
	LCD_RS=0;
	PORTD = ((instr>>4)&0x0f);
	LCD_En=0;
	LCD_En=1;
	LCD_RS=0;
	PORTD = ((instr)&0x0f);
	LCD_En=0;

	_delay_ms(400);
	_delay_ms(400);

*/
}

void lcd_reset()
{
	PORTD = 0xFF;
        _delay_ms(50);
        PORTD = 0x03+LCD_EN;
		_delay_ms(20);
        PORTD = 0x03;
    //    lcd_instr(0x03);
		_delay_ms(50);
        PORTD = 0x03+LCD_EN;
		_delay_ms(20);
        PORTD = 0x03;
		//lcd_instr(0x03);
		
        _delay_ms(10);
        PORTD = 0x03+LCD_EN;
		_delay_ms(20);
        PORTD = 0x03;
		//lcd_instr(0x03);
		
        _delay_ms(10);
        PORTD = 0x02+LCD_EN;
		_delay_ms(20);
        PORTD = 0x02;
		//lcd_instr(0x02);
		
        _delay_ms(30);
/*
	PORTD =0xFF;
	LCD_RS=1;
	LCD_En=1;
	_delay_ms(20);
	LCD_En = 1;
	LCD_RS = 0;
	PORTD = 0x03;
	LCD_En = 1;
	LCD_RS = 0;
	
	LCD_En=0;	
	_delay_ms(10);
	LCD_En = 1;
	LCD_RS = 0;
	PORTD = 0x03;
	LCD_En=0;	
	_delay_ms(1);
	LCD_En = 1;
	LCD_RS = 0;
	PORTD = 0x03;
	LCD_En=0;	
	_delay_ms(1);
	LCD_En = 1;
	LCD_RS = 0;
	PORTD = 0x02;
	LCD_En=0;	
	_delay_ms(1);
*/

}


void lcd_write_data(unsigned char dat)
{
 PORTD = (((dat >> 4) & 0x0F)|LCD_EN|LCD_RS);
  _delay_ms(20);
       PORTD = (((dat >> 4) & 0x0F)|LCD_RS);
       
        PORTD  = ((dat & 0x0F)|LCD_EN|LCD_RS);
		 _delay_ms(20);
        PORTD  = ((dat & 0x0F)|LCD_RS);

        _delay_ms(20);
        _delay_ms(20);
/*
	LCD_En=1;
	LCD_RS=1;
	PORTD = ((c>>4)&0x0f);
	LCD_En=0;
	LCD_En=1;
	LCD_RS=1;
	PORTD = ((c)&0x0f);
	LCD_En=0;

	_delay_ms(400);
	_delay_ms(400);
*/


}
void lcd_init()
{
_delay_ms(5);
	lcd_instr(0x28);       // 4-bit mode - 2 line - 5x7 font. 
        lcd_instr(0x0F);       // Display no cursor - no blink.
        lcd_instr(0x06);       // Automatic Increment - No Display shift.
        lcd_instr(0x01);
}

int main()
{
	lcd_reset();
	lcd_init();
/*	while(1)
	{
	lcd_instr(0x01);
	
_delay_ms(50);
	lcd_write_data('s');

_delay_ms(500);
	}*/
    return 0;
}


