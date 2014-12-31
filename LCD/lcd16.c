/*
 * CFile1.c
 *
 * Created: 31/12/2014 12:50:17
 *  Author: tedy.saputro
 */ 

#include "lcd16.h"
#include <util/delay.h>
void lcdcmd(unsigned char Data)
{

	PORTB &= ~RS; //because sending command
	PORTB  &=~EN;
	PORTB &=~RW;
	PORTB &= 0x0f;

	PORTB |= ((Data ) & 0xf0);
	PORTB &=~RW;
	PORTB  |=EN;
	_delay_ms(2);
	PORTB  &=~EN;

	PORTB &= 0x0f;

	PORTB  |= ((Data<<4) &  0xf0);
	PORTB  |=EN;
	_delay_ms(2);
	PORTB  &=~EN;


}
void lcdData(unsigned char l)
{
	PORTB |=RS;  //because sending data
	PORTB &=~RW;
	PORTB  &=~EN;
	PORTB &= 0x0f;
	PORTB |=((l ) & 0xf0);
	PORTB &=~RW;
	PORTB  |=EN;
	_delay_ms(2);
	PORTB  &=~EN;
	PORTB &= 0x0f;
	PORTB  |= ((l<<4) &  0xf0);
	PORTB  |=EN;
	_delay_ms(2);
	PORTB  &=~EN;



}

void lcdInit(void)
{
	PORTB &=~RS;
	PORTB  &=~EN;
	PORTB &=~RW;
	PORTB |= 0x30;
	_delay_ms(40);
	PORTB  |=EN;
	PORTB  &=~EN;
	_delay_ms(5);
	PORTB  |=EN;
	PORTB  &=~EN;
	_delay_ms(5);
	PORTB  |=EN;
	PORTB  &=~EN;
	_delay_ms(2);

	PORTB &= 0x20;
	PORTB  |=EN;
	PORTB  &=~EN;
	lcdcmd(0x28);   //set data length 4 bit 2 line
	_delay_ms(50);
	lcdcmd(0x0E);   // set display on cursor on blink on
	_delay_ms(50);
	lcdcmd(0x01); // clear lcd
	_delay_ms(50);
	lcdcmd(0x06);  // cursor shift direction
	_delay_ms(50);
	lcdcmd(0x80);  //set ram address
	_delay_ms(50);
}



void prints(const char *s)
{

	while (*s)
	{
		lcdData(*s);
		s++;
	}
}

void gotoXy(unsigned char  x,unsigned char y)
{
	if(x<40)
	{
		if(y) x |= 0x40;
		x |=0x80;
		lcdcmd(x);
	}

}
void integerToLcd(int integer )
{

	unsigned char thousands,hundreds,tens,ones;
	thousands = integer / 1000;

	lcdData(thousands + 0x30);

	hundreds = ((integer - thousands*1000)-1) / 100;

	lcdData( hundreds + 0x30);
	tens=(integer%100)/10;

	lcdData( tens + 0x30);
	ones=integer%10;

	lcdData( ones + 0x30);
}
