/*
 *  328_lcd.c
 *
 *  Introducion to Embedded Systems - CSE537, Monsoon 2011
 * 
 *  Assignment 1 : Interfacing the controller with LCD screen and display your name
 *
 *  Controller   : ATmega328P
 *  LCD Display  : JHD162A
 *
 *  Libraries    : LCD interface library(lcd.h,lch.c) from Peter Fleury(http://jump.to/fleury)
 *                 Accurate delay(delay_x.h) from Hans-Juergen Heinrichs
 * 
 *  Schematic (4bit data lines)
 *   
 *  ATmega328P  JHD162A
 *   Gnd -------- VSS
 *    5V -------- VCC
 *   Gnd _/\1K/\- VEE
 *
 *   PC0 -------- RS
 *   PC1 -------- R/W
 *   PC2 -------- RE
 *
 *   PD2 -------- DB4
 *   PD3 -------- DB5
 *   PD4 -------- DB6
 *   PD5 -------- DB7
 * 
 *  3.3V _/\1K/\- LED+
 *   Gnd -------- LED- 
 * 
 *  
 *  Flashing
 *    mode COM4 57600
 *    avrdude -P COM4 -b 57600 -p m328p -c AVRISP -F -e -U flash:w:328_lcd.hex 
 *    pause
 *
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"

int main()
{
   lcd_init(LCD_DISP_ON);
   _delay_ms(100);   
   
   //lcd_command( (1<<LCD_MOVE) | (1<<LCD_MOVE_RIGHT) );
   //_delay_ms(10);

   while(1)
   {
      lcd_clrscr();
	  _delay_ms(1000);
      lcd_puts("SamY");
	  _delay_ms(1000);
   }

   return 0;
}


