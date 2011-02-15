//Prateek Gaur 2008039


#define F_CPU 16000000UL
#define Dev24C08 0xA0
#include<avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include "i2cmaster.h"
#include "twimaster.c"

int main(){

unsigned int adc_value,k;
	
    unsigned int  checkret;
    int i=0;
    unsigned int average=0;
    int c=0x00;
	char str[100];
	
    
lcd_init(LCD_DISP_ON);           //setting the led
lcd_clrscr();
_delay_ms(1000);


        i2c_init();             //initializing the eeprom
		lcd_clrscr();                 //for checking if lcd is working correctly
	  _delay_ms(100);	  
    


	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

	//No MUX values needed to be changed to use ADC0

	ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADEN);  // Enable ADC

	//ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt
	//sei();   // Enable Global Interrupts        
	//global interrupts are disabled as the hamper the working of the eeprom          

	ADCSRA |= (1 << ADSC);  // Start A2D Conversions


		
	while(1)
	{
      	checkret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
     for(i=0;i<30;i++)                    //reading at a delay of 100 ms means reading 
	 {                                    // 10 samples per second
	    adc_value=ADCL;
		adc_value|=(ADCH<<8);
		//adc_value=adc_value;   //conversion factor to calculate the Temp. from adc value
		k=adc_value/4;              //dividing by 2^2 so as to fit in 8 bit address
	
        /* issuing start condition ok, device accessible */
        i2c_write(c);                       
        i2c_write(k);
		
		_delay_ms(100);
	 }                        
        i2c_stop();                            // set stop conditon = release bus
       		lcd_clrscr();   
			_delay_ms(1000);                    
			lcd_puts("written in eeprom");            //showing writing has been done at              
			_delay_ms(1000);                // at 10 Hz
        
		c=0x00;                          // initializing the address counter for reading
		
		for(i=0;i<30;i++)
		{
		i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
        i2c_write(c);                        
        i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode
        checkret = i2c_readNak();                    // read one byte
        i2c_stop();                     //As reading with NAK so stop condition in every cycle
        checkret=checkret*2;
		average+=checkret;
		c++;                                //incrementing the address counter
       }
		
		
		 average=average/30;
		 lcd_clrscr();		 
	    _delay_ms(1000);	
		sprintf(str, "average : %d",average);  
        lcd_puts(str);	  
	    _delay_ms(1000);
       
}
}
