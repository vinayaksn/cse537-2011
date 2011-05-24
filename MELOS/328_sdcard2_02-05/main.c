#define F_CPU 16000000UL

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define DEBOUNCE_TIME 25        /* time to wait while "de-bouncing" button */
#define LOCK_INPUT_TIME 250     /* time to wait after a button press */

#define LOGFILENAME "log.txt"

#include <stdio.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "delay_x.h"
//#include "USART328.c"
#include "sdcard/uart.h"
#include <avr/sfr_defs.h>

int button1_is_pressed();
int portbit1_is_clear();
int button2_is_pressed();
int portbit2_is_clear();
int button3_is_pressed();
int portbit3_is_clear();
int button4_is_pressed();
int portbit4_is_clear();
int button5_is_pressed();
int portbit5_is_clear();
int button6_is_pressed();
int portbit6_is_clear();
int button7_is_pressed();
int portbit7_is_clear();
int button8_is_pressed();
int portbit8_is_clear();

// from fat main.c
int init_sdcard();
int create_file( const char* fname );
int delete_file( const char* fname );
int display_file(const char* fname);
int write_data(const char* fname, unsigned int data);
int write_data_block(const char* fname, uint8_t *data, int length);

#include "adc.h"

int main (void)
{

   DDRC  |= (1<<1);
   DDRD  &= ~ ((1<<2)|(1<<3)|(1<<4)|(1<<5));   // PD2->MSB and PD5->LSB
   DDRD |= (1<<6);   // BT module control
   DDRD |= (1<<7);   // SD card module control

   PORTC &= ~(1<<1);  // Relay
   PORTD |= (1<<7);  // SD card

   //   USART_init(MYUBRR);
   uart_init();
   adc_init();

   //uart_puts_p(PSTR("initializing SDcard.."));
   init_sdcard();
   delete_file( LOGFILENAME );
   //create file
   while( create_file (LOGFILENAME) != 0 )
	   ;

   for(;;)  // Loop Forever
   {

	   //uart_puts_p(PSTR("test"));

   if (button1_is_pressed())
   {
	   //ADC on
	   //uart_puts_p(PSTR(" ADC On \r\n"));
	   sei();
   }
   else if (button2_is_pressed())
   {
	   cli();
	   uart_puts_p(PSTR(" ADC Off \r\n"));
      _delay_ms(LOCK_INPUT_TIME);

    }


  else if (button3_is_pressed())
   {
       PORTD |=(1<<6);
	  _delay_ms(LOCK_INPUT_TIME);

	  // Setup time for BT
	  // ???? Modify this based upon ACK later
	  //_delay_ms(5);

      _delay_s(5);
      display_file(LOGFILENAME);
      uart_putc('#');

    }
  else if (button4_is_pressed())
   {
	  uart_puts_p(PSTR(" BT Off \r\n"));
      PORTD &=~(1<<6);
	  _delay_ms(LOCK_INPUT_TIME);
    }
else if (button5_is_pressed())
   {
	PORTC |= (1<<1); // relay on
	_delay_ms(LOCK_INPUT_TIME);
    }
else if (button6_is_pressed())
   {
	PORTC &= ~(1<<1);  //relay off
	_delay_ms(LOCK_INPUT_TIME);
    }
else if (button7_is_pressed())
   {
	uart_puts_p(PSTR("SD On \r\n"));
	PORTD |= (1<<7); // SDcard On
	_delay_ms(LOCK_INPUT_TIME);
    }
else if (button8_is_pressed())
   {
	uart_puts_p(PSTR("SD Off \r\n"));

	PORTD &= ~(1<<7); // SDcard off
	_delay_ms(LOCK_INPUT_TIME);
   }
else
   {

	uart_puts_p(PSTR(" No Key Pressed \n "));
      _delay_ms(LOCK_INPUT_TIME);
    }

   }//forever
}

int button1_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit1_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit1_is_clear())
			     return 1;
        }

        return 0;
}


int portbit1_is_clear()
{

if ((!(PIND & (1<<2))) && (!(PIND & (1<<3))) && (!(PIND & (1<<4))) && ((PIND & (1<<5))) )
return 1;

else
return 0;

}



int button2_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit2_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit2_is_clear())
			     return 1;
        }

        return 0;
}


int portbit2_is_clear()
{

if ((!(PIND & (1<<2))) && (!(PIND & (1<<3)))&& ((PIND & (1<<4))) && (!(PIND & (1<<5))) )
return 1;

else
return 0;

}


int button3_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit3_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit3_is_clear())
			     return 1;
        }

        return 0;
}


int portbit3_is_clear()
{

if ((!(PIND & (1<<2))) && (!(PIND & (1<<3)))&& ((PIND & (1<<4))) && ((PIND & (1<<5))) )
return 1;

else
return 0;

}

int button4_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit4_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit4_is_clear())
			     return 1;
        }

        return 0;
}


int portbit4_is_clear()
{

if ((!(PIND & (1<<2))) && ((PIND & (1<<3)))&& (!(PIND & (1<<4))) && (!(PIND & (1<<5))) )
return 1;

else
return 0;

}

int button5_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit5_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit5_is_clear())
			     return 1;
        }

        return 0;
}


int portbit5_is_clear()
{

if ((!(PIND & (1<<2))) && ((PIND & (1<<3)))&& (!(PIND & (1<<4))) && ((PIND & (1<<5))) )
return 1;

else
return 0;

}


int button6_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit6_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit6_is_clear())
			     return 1;
        }

        return 0;
}


int portbit6_is_clear()
{

if ((!(PIND & (1<<2))) && ((PIND & (1<<3)))&& ((PIND & (1<<4))) && (!(PIND & (1<<5))))
return 1;

else
return 0;

}

int button7_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit7_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit7_is_clear())
			     return 1;
        }
        return 0;
}

int portbit7_is_clear()
{
	if ((!(PIND & (1<<2))) && ((PIND & (1<<3)))&& ((PIND & (1<<4))) && ((PIND & (1<<5))) )
		return 1;
	return 0;
}

int button8_is_pressed()
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (portbit8_is_clear())
        {
                _delay_ms(DEBOUNCE_TIME);
                if (portbit8_is_clear())
			     return 1;
        }
        return 0;
}

int portbit8_is_clear()
{
	if (((PIND & (1<<2))) && (!(PIND & (1<<3)))&& (!(PIND & (1<<4))) && (!(PIND & (1<<5))) )
		return 1;
	return 0;
}
