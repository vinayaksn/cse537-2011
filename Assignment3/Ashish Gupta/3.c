#define F_CPU 16000000UL
#include <avr/io.h>
#include<stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include "i2cmaster.h"
#include "twimaster.c"


#define Dev24C02  0xA2      // device address of EEPROM 24C02, see datasheet

int sum=0;
unsigned char ret;
unsigned int read;
char buf [100];

int main(void)
{

	
	
 	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	_delay_ms(1000);
   	
	lcd_clrscr();
  	_delay_ms(100);
	lcd_puts("EEPROM");	  
 	 _delay_ms(1000);
	
	temp_init();
    i2c_init();                                // init I2C interface
	
	while(1){
	
	temp_sense();
	
        /* write ok, read value back from eeprom address 0x05, wait until 
           the device is no longer busy from the previous write operation */
        
		
	/*	for(int i=0;i<15;i++)
		{
			
		}
		read = i2c_readNak();
		sprintf( buf, "read is: %d", read );
			sum = sum+ read;
			lcd_clrscr();
	  		_delay_ms(100);
			lcd_puts(buf);	  
	 	 	_delay_ms(1000); 
	*/	

		int average = sum/30;
			sprintf( buf, "Sum is: %d", sum );
			lcd_clrscr();
	  		_delay_ms(100);
			lcd_puts(buf);	  
	 	 	_delay_ms(1000);

			sprintf( buf, "Average is: %d", average );
			lcd_clrscr();
	  		_delay_ms(100);
			lcd_puts(buf);	  
	 	 	_delay_ms(1000);	
}

}

void temp_init(){
	lcd_clrscr();
 	_delay_ms(100);
	lcd_puts("Starting ADC");	  
	_delay_ms(1000);

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz      
        
   ADMUX |= (1 << REFS0); // set refrence voltage
  // ADMUX |= (0 << ADLAR); // left adjust ADC result.

   ADCSRA |= (1 << ADATE); // Set ADC to Free-Running Mode
   
   ADCSRA |= (1 << ADEN); // Enable ADC 
   
   //ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt
   
   ADCSRA|=(1<<ADSC);		// Start A2D Conversions
}

void temp_sense(){
	unsigned char ret;
	unsigned int write;
		lcd_clrscr();
 	_delay_ms(100);
	lcd_puts("Sensing Now");	  
	_delay_ms(1000);	
	sum=0;

	for(int i=0;i<30;i++)
	{
		unsigned int adc;
    	double temp;
		adc = ADCL; 
    	adc |= (ADCH<<8); //left shift 
		char value[100];

	//The implementation of the steinhart equation.
	
		float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
		float R = 1000.0; 			// Fixed resistance in the voltage divider
		float logRt,Rt;
		int T;
		int Vo = adc;
		Rt = R*( 1023.0 / (float)Vo - 1.0 );
		logRt = log(Rt);
		T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;   //SteinHart equation implementation
		itoa(T, value, 10);
    
	    /*lcd_clrscr();
    	_delay_ms(1000);
    	lcd_puts("Temp=");
		lcd_puts(value);
		lcd_puts("*C");
        _delay_ms(1000);*/
		
		ret = i2c_start(Dev24C02+I2C_WRITE);       // set device address and write mode
		i2c_write(0x00);                       // write address = 5

		//write to eeprom
    	  if ( ret ) 
		  {
			lcd_clrscr();
	  		_delay_ms(100);
			lcd_puts( "Error.." );	  
	  		_delay_ms(1000);
        	/* failed to issue start condition, possibly no device found */
        	i2c_stop();
    	  }
		
		else{          /* issuing start condition ok, device accessible */
			write = T;
			i2c_write(write);                       // ret=0 -> Ok, ret=1 -> no ACK 
			i2c_stop();
		}

		i2c_start_wait(Dev24C02+I2C_WRITE);     // set device address and write mode
        i2c_write(0x00);                        // write address = 5
        i2c_rep_start(Dev24C02+I2C_READ);       // set device address and read mode
    	read = i2c_readNak();                    // read one byte
		sprintf( buf, "read is: %d", read );
		sum = sum+ read;
		//lcd_clrscr();
	  	_delay_ms(100);
		//lcd_puts(buf);	  
	 	//_delay_ms(1000);
		i2c_stop();
		sum = sum + read;
	}
	                            // set stop conditon = release bus
	
}


