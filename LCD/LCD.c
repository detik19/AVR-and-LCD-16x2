/*
 * Atmega_16_Learn.c
 *
 * Created: 9/23/2012 8:46:23 PM
 *  Author: Thanks to Gaurav
 */ 

#include <avr/io.h>
#include <stdio.h>

#define F_CPU 4000000UL
#include <util/delay.h>
#include "lcd16.h"



int main(void)
{
		
	
	unsigned int temp;
	
	DDRB = 0xFF;		//set the PORTB Direction Set every pin of PORTB as out as our lcd on this
	

	
	
	lcd_init();
	lcd_clear();

	lcd_putsf("Halo dari LCD");
	_delay_ms(500);
 
		
		
		
		temp = 12;

		lcd_gotoxy(1,1 );			//set the cursor to 1 column of 1st row
		lcd_putsf("Hay!");		
		lcd_putInt(temp);		// print adc value to the lcd
		_delay_ms(500);
		
		lcd_clear();
		lcd_putsf("bersih123");
		
		_delay_ms(500);
		lcd_clear();
		lcd_putchar('g');
		_delay_ms(500);

}
