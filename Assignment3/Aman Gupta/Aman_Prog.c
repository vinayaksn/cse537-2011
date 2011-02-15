#define F_CPU 16000000UL
#include <avr/io.h>

#include "lcd.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delay_x.h"
#include "i2cmaster.h"


#define Dev24C08 0xA0





int main()
{

	unsigned int connect, read_ack;
	char buffer[10];
	
	lcd_init(LCD_DISP_ON);
	_delay_ms(500);
	lcd_clrscr();
	_delay_ms(1000);

	lcd_puts("Hello");
	_delay_ms(1000);
	i2c_init();

	while(1)
	{
	
	connect=i2c_start(Dev24C08+I2C_WRITE);

	if(connect)
	{
		i2c_stop();
		lcd_puts("Not able to connect to the EEPROM");
	}
	else
	{
		i2c_write(0x00);
		unsigned int tempadc;
 		for(int i=0;i<30;i++)
		{
			
			int adcval;
		
			adcval=adc();
			tempadc=adcval/4;
			
			i2c_write(tempadc);
			_delay_ms(100);
			
		}

		i2c_stop();
		int count=0x00;

		int tot=0;

		i2c_start_wait(Dev24C08+I2C_WRITE);
		i2c_write(0x00);
		i2c_rep_start(Dev24C08+I2C_READ);

        lcd_clrscr();
		//_delay_ms(100);
        //sprintf(buffer,"The : %d",average);
        lcd_puts("In Progress");
		_delay_ms(10000);
		for(int i=0;i<29;i++)
		{
		   
           read_ack = i2c_readAck(); 
		   read_ack = read_ack*4;
		   tot=tot+read_ack;
		   
        }

		 read_ack = i2c_readNak(); 
		i2c_stop();
		read_ack = read_ack*4;
		tot+=read_ack;

		int average = tot/30;
        lcd_clrscr();
		//_delay_ms(100);
        sprintf(buffer,"The : %d",average);
        lcd_puts(buffer);
		_delay_ms(1000);

	}
	}

}

int adc()
{

/*lcd_puts("in function");
_delay_ms(100);*/
int x=0;


	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (0 << MUX1) | (0 << MUX0)|(0 << MUX2);
	
	ADMUX |= (1 << REFS0);
	ADMUX |= (0 << ADLAR);
	
	//ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);

			x=ADCL;
		x|=(ADCH<<8);
		
		return x;
	
} 
