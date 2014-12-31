/*
 * CFile1.c
 *
 * Created: 31/12/2014 12:50:17
 *  Author: tedy.saputro
 */ 

#include "lcd16.h"
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

const uint8_t LcdCustomChar[] PROGMEM=//define 8 custom LCD chars
{
	0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, // 0. 0/5 full progress block
	0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, // 1. 1/5 full progress block
	0x00, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, // 2. 2/5 full progress block
	0x00, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x00, // 3. 3/5 full progress block
	0x00, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x00, // 4. 4/5 full progress block
	0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // 5. 5/5 full progress block
	0x03, 0x07, 0x0F, 0x1F, 0x0F, 0x07, 0x03, 0x00, // 6. rewind arrow
	0x18, 0x1C, 0x1E, 0x1F, 0x1E, 0x1C, 0x18, 0x00  // 7. fast-forward arrow
};

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

void LCDsendCommand(uint8_t cmd)	//Sends Command to LCD
{
	
	//4 bit part
	LDP=(cmd&0b11110000);
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP=((cmd&0b00001111)<<4);
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	
}

void LCDsendChar(uint8_t ch)		//Sends Char to LCD
{

	
	//4 bit part
	LDP=(ch&0b11110000);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LDP=((ch&0b00001111)<<4);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	
}
void LCDdefinechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a=(char_code<<3)|0x40;
	for (i=0; i<8; i++){
		pcc=pgm_read_byte(&pc[i]);
		LCDsendCommand(a++);
		LCDsendChar(pcc);
	}
}

void lcd_init(void)//Initializes LCD
{
	
	//4 bit part
	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCDR|=1<<LCD_E|1<<LCD_RW|1<<LCD_RS;
	//---------one------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-----------two-----------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-------three-------------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //4 bit mode
	LCP|=1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------4 bit--dual line---------------
	LCDsendCommand(0b00101000);
	//-----increment address, invisible cursor shift------
	LCDsendCommand(0b00001100);
	//init 8 custom chars
	uint8_t ch=0, chn=0;
	while(ch<64)
	{
		LCDdefinechar((LcdCustomChar+ch),chn++);
		ch=ch+8;
	}


	


	
}
/*
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
*/
void lcd_clear()
{
	lcdcmd(1<<LCD_CLR); 
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
