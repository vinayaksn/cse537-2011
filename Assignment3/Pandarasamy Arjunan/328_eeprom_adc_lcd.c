/*
 *  328_eeprom_adc_lcd.c
 *
 *  Introducion to Embedded Systems - CSE537, Monsoon 2011
 * 
 *  Assignment 3 : Interface an external EEPROM with the microcontroller. 
 *				   Collect the sensor data at 10 Hz, store it in the EEPROM and every 3 seconds,
 *				   compute the average of the historical data and display it on the LCD.
 *
 *  Controller   : ATmega328P
 *  LCD Display  : JHD162A
 *  Temp Sensor  : LM35
 *  EEPROM		 : AT24C08
 *
 *  Libraries    : LCD interface library(lcd.h,lch.c) from Peter Fleury(http://jump.to/fleury)
 *                 Accurate delay(delay_x.h) from Hans-Juergen Heinrichs
 *				   I2C Library from Peter Fleury  
 *   			   http://homepage.hispeed.ch/peterfleury/group__pfleury__ic2master.html
 * 
 *  Schematic (4bit data lines)
 *   
 *  ATmega328P  JHD162A
 *   Gnd -------- VSS
 *    5V -------- VCC
 *   Gnd _/\1K/\- VEE
 *
 *   PC1 -------- RS
 *   PC2 -------- R/W
 *   PC3 -------- RE
 *
 *   PD2 -------- DB4
 *   PD3 -------- DB5
 *   PD4 -------- DB6
 *   PD5 -------- DB7
 * 
 *  3.3V _/\1K/\- LED+
 *   Gnd -------- LED- 
 * 
 * 				EEPROM
 *   PC4 -------- SDA
 *   PC4 -------- SCL
 *   
 */


#define F_CPU 16000000UL

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


#include <avr/io.h>
#include <stdio.h>
#include <assert.h>
#include <avr/interrupt.h>
#include <math.h>
//#include <mem.h>

#include "USART328.c"
#include "delay_x.h"
#include "i2cmaster.h"
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"


#define Dev24C08  0xA2      // device address 

void ADC_init();
void lcd_write_str(char *s);
void eeprom_write_byte(unsigned char addr, unsigned char data );
void eeprom_write_str(unsigned char addr, char *str );
void eeprom_read_str(unsigned char addr, char *str, int len );

unsigned int volatile  adc_count;
unsigned char volatile eeprom_addr;


int main()
{
	unsigned char rc;	
	char buf[100];	
	unsigned long i, count, sum;


	USART_init(MYUBRR);

	i2c_init();
	ADC_init();
	lcd_init(LCD_DISP_ON);
   _delay_ms(100);   

		// check eeprom
	rc = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
	if ( rc ) {	        
	        i2c_stop();
			USART_String("EEPROM failed\r\n");
			lcd_write_str("EEPROM failed\r\n");
			return 1;
	    }


	while(1)
	{	
		_delay_ms(3000);

		i2c_start_wait(Dev24C08+I2C_WRITE);
	    i2c_write(1); 	
	    i2c_rep_start(Dev24C08+I2C_READ);
	        
		sum = 0;
		count = eeprom_addr;
		for( i=1; i<count-1; ++i)
		{		
			sum += i2c_readAck();
		}
		sum += i2c_readNak();
		i2c_stop();

		sprintf(buf, "TEMP : %d", (int)(ceil((double)sum/count)) );	// floating is not supported
		lcd_write_str(buf);
		sprintf( buf, "%s\r\n", buf );
		USART_String(buf);

	}

	return 0;
}


ISR(ADC_vect)
{	
	++adc_count;

	/* 
	 * ADC ISR was called 11406 in average per second on test, not sure why )
	 * 11406 / 10 = 1140 for 10hz 
	 * 
	 */
	if( adc_count == 1140 )
	{
		adc_count = 0;		
		eeprom_addr ++;

		eeprom_write_byte(eeprom_addr, (unsigned char) (ADC * 0.488) );
	}

}

void ADC_init()
{
 	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz   
 	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC


	ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode 
   ADCSRA |= (1 << ADEN);  // Enable ADC 

   ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt 
   sei();   // Enable Global Interrupts 

   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
}


void lcd_write_str(char *s)
{
	lcd_clrscr();
     _delay_ms(100);
     lcd_puts(s);
     _delay_ms(100);
}


void eeprom_write_byte(unsigned char addr, unsigned char data )
{
	i2c_start_wait(Dev24C08+I2C_WRITE);
	i2c_write(addr);
	i2c_write(data);
	i2c_stop();

	// for debugging
	char b[20];
	sprintf( b, "current temp : %d\r\n", (unsigned char) (ADC * 0.488) );
	USART_String(b);

}
