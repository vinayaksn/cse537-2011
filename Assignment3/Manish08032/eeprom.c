#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include<string.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include "twimaster.c"
#include "lcd.h"


#define Dev24C02  0xA0      // device address of EEPROM 24C02, see datasheet


uint16_t ReadADC()
   {
      

   ADCSRA|=(1<<ADSC);//Start Single conversion

   
   while(!(ADCSRA & (1<<ADIF)));//Wait for conversion to complete
		


   
   ADCSRA|=(1<<ADIF);//Clear ADIF by writing one to it
    
   return(ADCL);
 }


int main(void)
 {
	
	uint8_t j;
	int result;
	
	unsigned char ret,data;
	uint16_t adc_value;
  
  	uint16_t t;
    char rslt[10];
	char tmp[6]="temp=";

   lcd_init(LCD_DISP_ON);
   lcd_puts("testing....");
   _delay_ms(1000);
   
	 lcd_clrscr();
      
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz      

   ADMUX |= (1 << REFS0); // set refrence voltage

   //ADMUX |= (1 << ADLAR); // left adjust ADC result.

   ADCSRA |= (1 << ADEN);  // Enable ADC 

   i2c_init();                                
  ret = i2c_start(Dev24C02+I2C_WRITE);// set device address and write mode

    if ( ret ) {
        /* failed to issue start condition, possibly no device found */
        i2c_stop();
        lcd_puts("Error...");
		_delay_ms(1000);
			exit(0);	        
    }
	else
	
	{

    i2c_write(0x00);                       // write address = 0
	i2c_stop();	
   uint8_t i = 0;
  
  
 	 while(1)
  		{
      	  	 

      i2c_start_wait(Dev24C02+I2C_WRITE);     // set device address and write mode
        i2c_write(0x00);                        // write address = 0
      
	 strcpy(tmp,"Temp=");
	  
    for(i=1;i<=30;i++)
	{ 
	   _delay_ms(100);
      adc_value= ReadADC();//Read ADC
       adc_value|=(ADCH<<8);
      t= adc_value/2;//Convert to degree Centrigrade
         
	   i2c_write(t);
	   itoa(t,rslt,10);
	   lcd_clrscr();
	   lcd_puts(rslt);
	   
      	}

      i--;

	 i2c_stop();
	 lcd_clrscr();                          
     lcd_puts("done");
	 _delay_ms(500);
	i2c_start_wait(Dev24C02+I2C_WRITE);      // set device address and write mode
        i2c_write(0x00);
	i2c_rep_start(Dev24C02+I2C_READ);        
         
	lcd_puts("reading...");
	 _delay_ms(1000);


    result=0;

	 for(j=1;j<=30;j++)//reading the written readings                     
	   {  		                          
	   if(j==30)
		result=result+(int)i2c_readNak(); 	

		else
	   result=result+(int)i2c_readAck();   
	   
	   }

       i2c_stop();
    	 j--;

	    
   lcd_clrscr();
   result = result/j;
	 
   itoa(result,rslt,10);
   
   strcat(tmp,rslt);

   lcd_puts(tmp);
    _delay_ms(1000);
   lcd_clrscr();
      	  

    }// end of while 
     	 
  }// end of else
return 0 ;

} //end 
   


 
  
      

