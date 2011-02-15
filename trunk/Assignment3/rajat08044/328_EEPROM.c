#define F_CPU 16000000UL
#define Dev24C08 0xA0

#include<avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include "i2cmaster.h"
#include "twimaster.c"




int main()
{
	int avg=0, sum=0, i;
	unsigned int out;
	unsigned char ret;
	int count=0x00;
	char buf[10];

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	_delay_ms(1000);
	i2c_init();

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

	//No MUX values needed to be changed to use ADC0

	ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADEN);  // Enable ADC

	ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt
	
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions


	while(1)
	{
		unsigned int vt;
		count=0x00;
		for(i=0; i<16; i++)
		{
			ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
			unsigned int adc_value;
			adc_value=ADCL;
			adc_value|=(ADCH<<8);
			char value[8];
			float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
			float R=1000.0; 			// Fixed resistance in the voltage divider
			float logRt,Rt,T;
			int Vo = adc_value;
			Rt = R*( 1023.0 / (float)Vo - 1.0 );
			logRt = log(Rt);
			T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;   //SteinHart equation implementation
			itoa((int)T, value, 10);
	
	        i2c_write(0x00);                      
    	    i2c_write((int)20);
			count++;
			_delay_ms(100);
		}    
		sprintf( buf, "Value : %d", count);
		lcd_puts(buf);
		_delay_ms(1000);                   
        i2c_stop();   
		
		count=0x00;
		lcd_clrscr();
		_delay_ms(100);  
		sum=0;                      
		for(i=0;i<16;i++)
		{
			//lcd_clrscr();
			//_delay_ms(100);
			i2c_start_wait(Dev24C08+I2C_WRITE);
        	i2c_write(count);              
        	i2c_rep_start(Dev24C08+I2C_READ);
			out = i2c_readNak();
			sum  = sum + (int)out;
			//sprintf( buf, "Value : %d %d",  out, count);
			//lcd_puts(buf);
			//_delay_ms(100);
			count++;
		}                 
		avg = (int)(sum/30); 
		//lcd_clrscr();
		//_delay_ms(100); 
		sprintf( buf, "Avg:%d", avg);
		lcd_puts(buf);
		_delay_s(1);
        i2c_stop();
	}
}
