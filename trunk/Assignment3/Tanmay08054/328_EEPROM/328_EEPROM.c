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

#include <avr/interrupt.h> 
int adc_val()
{
// DDRD =140;
	int x=-1,y=-1;
   
 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
 

   ADMUX |= (0 << ADLAR);
  
  
  

	

	//ADCSRA |= (1 << ADSC);
	//ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADATE);

	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);       	
	
	
	lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_clrscr();
   _delay_ms(1000);

   _delay_ms(10);
      
   

//while(1)  // Loop Forever 
  // { 
   
  //_delay_s(3);
	x= ADCL; 
	x |= (ADCH<<8); //left shift 
	
  char buf[10];
	sprintf( buf, "%d\n", x );
	
return x;
	                                                                    
       //  lcd_clrscr();
	 // _delay_ms(1000);	  
	  
     // lcd_puts(buf);	  
	
	  //_delay_ms(1000);
//	ADCSRA |= (1 << ADSC);       	  
	 //_delay_ms(1000);

   //}

}
int main(){


unsigned char temp, ret;
unsigned int input=0;

char buf[10];
lcd_init(LCD_DISP_ON);
lcd_clrscr();
_delay_ms(1000);

int counter=0,avg=0;
int address=0x05;
i2c_init();
		lcd_clrscr();
	  _delay_ms(100);	  
      lcd_puts("EEPROM started");	  
	  _delay_ms(1000);

	ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
    
	while(counter<10)
	{
	
        i2c_write(address);                       // write address = 5
		input=adc_val();
		input=input/4;
        i2c_write('input');                       // ret=0 -> Ok, ret=1 -> no ACK 
		
                                    // set stop conditon = release bus
		counter++;
}
        i2c_stop();/* write ok, read value back from eeprom address 0x05, wait until 
           the device is no longer busy from the previous write operation */
     counter=0;   
	while(counter<10)
	{
		i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
        i2c_write(address);                        // write address = 5
        i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode
        ret = i2c_readNak();                    // read one byte
        i2c_stop();
		avg=avg+(int)ret;
		address++;
    counter++;
	}
	avg=avg/10;
	avg=avg*4;
	sprintf( buf, "avg : %d", avg );
	 
		lcd_clrscr();
	  _delay_ms(100);	  
      lcd_puts( buf );	  
	  _delay_ms(1000);


/*
i2c_start_wait(Dev24c08+I2C_WRITE);
i2c_write(0x00);

i2c_rep_start(Dev24c08+I2C_READ);


temp = i2c_readNak();
i2c_stop();
*/

while(1){
		lcd_clrscr();
	  _delay_ms(100);
lcd_puts(buf);
_delay_ms(1000);
}

}


