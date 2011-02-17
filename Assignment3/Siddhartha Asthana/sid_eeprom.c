
/*

Accessing External EEPROM AT24C08

*/

#define F_CPU 16000000UL

#define BAUD 9600

#include <avr/io.h>
#include <stdio.h>
#include <assert.h>
#include <avr/interrupt.h>
#include <math.h>
#include "delay_x.h"
#include "i2cmaster.h"
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"


#define Dev24C08  0xA2      // device address 

void ADC_init();
void lcd_write_str(char *s);
void eeprom_write_byte(unsigned char addr, unsigned char data );
void eeprom_read_str(unsigned char addr, char *str, int len );

unsigned int volatile  adc_count;
unsigned char volatile eeprom_addr;


int main()
{

	unsigned char ret, addr = 0xf0;
	char buffer[100];
	
	int len = 10;
	unsigned long i, count, sum;



	i2c_init();
	ADC_init();
	lcd_init(LCD_DISP_ON);
   _delay_ms(100);   

	    ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
	    if ( ret ) {	        
	        i2c_stop();
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

		sprintf(buffer, "TEMP : %d", (int)(ceil((double)sum/count)) );	// floating is not supported
		lcd_write_str(buffer);
	}
	

	return 0;
}


ISR(ADC_vect)
{	
	++adc_count;

	/* 
	 * ADC ISR was called 11406 in average per second on test )
	 * 11406 / 10 = 1140 for 10hz not sure why?
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

}


