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

int main(){


unsigned char  ret;

//char buf[10];
lcd_init(LCD_DISP_ON);
lcd_clrscr();
_delay_ms(1000);

	
        char buf[100];
        char write[10];
        
		

void temperature(){

ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz      
        
   ADMUX |= (1 << REFS0); // set refrence voltage

  // ADMUX |= (0 << ADLAR); // left adjust ADC result.

   ADCSRA |= (1 << ADATE); 
   
   ADCSRA |= (1 << ADEN); // Enable ADC 
   ADCSRA|=(1<<ADSC);

}

i2c_init();

		temperature();
/*  // FOR SINGLE READ WRITE
i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
        i2c_write(0x05);                       // write address = 5
        i2c_write(0x75);                       // ret=0 -> Ok, ret=1 -> no ACK 
        i2c_stop();                            // set stop conditon = release bus

        i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
        i2c_write(0x05);                        // write address = 5
        i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode
        ret = i2c_readNak();                    // read one byte
        i2c_stop();
    


	sprintf( buf, "read : %c", ret );
	 
		lcd_clrscr();
	  _delay_ms(100);	  
      lcd_puts( buf );	  
	  _delay_ms(1000);



lcd_clrscr();
	  _delay_ms(100);
lcd_puts("Read"+temp);
_delay_ms(1000);
*/
	lcd_clrscr();
	  _delay_ms(100);
		lcd_puts( "Reading" );	  
	  _delay_ms(1000);
	      	  
while(1){

		int average =0 ;
		//unsigned char  mem_W =0x05,mem_R =0x05;
		i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
		i2c_write(0x05);
		for(int i=0;i<15;i++)
		{
		unsigned int adc;
		int temp;
		 adc = ADCL; 
         adc |= (ADCH<<8); //left shift 
		 adc = adc / 5;
		 temp = adc;
	
		lcd_clrscr();
	  _delay_ms(100);
		lcd_puts( "Reading" );	  
	  _delay_ms(1000);
	      	  
		itoa((int)temp,buf,10);
		lcd_clrscr();
	  	_delay_ms(1000);
		lcd_puts(buf);
		_delay_ms(1000);
        i2c_write('a');       // set stop conditon = release bu
		}
 		
 		i2c_stop(); 

			lcd_clrscr();
	  _delay_ms(100);
lcd_puts( "Written" );	  
	  _delay_ms(1000);


	i2c_start_wait(Dev24C08+I2C_WRITE);// set device address and write mode
        
		i2c_write(0x05);                        // write address = 5
        	
		lcd_clrscr();
	  _delay_ms(100);
		lcd_puts( "Reading" );	  
	  _delay_ms(1000); 
		
		i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode
        
		for(int i=0;i<15;i++)
		{
			lcd_clrscr();
	  _delay_ms(100);
lcd_puts( "Reading" );	  
	  _delay_ms(1000);
	 	ret = i2c_readNak();
		average += (double) ret *5;                    // read one byte
    	}

		i2c_stop();
	
	
		average = average/30;

	  	itoa(average,buf, 10);                       // write address = 5
       
    	sprintf( buf, "read : %d", average );
	
	  lcd_puts( buf );	  


}

}
