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
	DDRA = 0xFE;		//set the PORTA Direction Set every pin of PORTA as out except AN0 
	DDRB = 0xFF;		//set the PORTB Direction Set every pin of PORTB as out as our lcd on this
	

	
	
	lcdInit();


	prints("LCD ATMEGA16");
	_delay_ms(500);
    	while(1)
    	{	
		
		ADCSRA |= 0x40;			// start the adc conversion on AN0
		while(ADCSRA & 0x40);
		temp = ADC;

		gotoXy(1,1 );			//set the cursor to 1 column of 1st row
		prints("ADC = ");		
		integerToLcd(temp);		// print adc value to the lcd

		
		_delay_ms(300);
		
	
   	 }
}
