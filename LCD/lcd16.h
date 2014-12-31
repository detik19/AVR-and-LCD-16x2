#ifndef __lcd16_h_
#define __lcd16_h_


#include <avr/io.h>


#define RS  0x01
#define EN  0x04
#define RW  0x02

#define LCD_CLR             0	//DB0: clear display

#define LDP PORTB	//define MCU port connected to LCD data pins
#define LCP PORTB	//define MCU port connected to LCD control pins
#define LDDR DDRB	//define MCU direction register for port connected to LCD data pins
#define LCDR DDRB	//define MCU direction register for port connected to LCD control pins
#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_RW	1 	//define MCU pin connected to LCD R/W
#define LCD_E	2	//define MCU pin connected to LCD E

#define LCD_D4	4	//define MCU pin connected to LCD D3
#define LCD_D5	5	//define MCU pin connected to LCD D4
#define LCD_D6	6	//define MCU pin connected to LCD D5
#define LCD_D7	7	//define MCU pin connected to LCD D6

#define LCD_DDRAM           7	//DB7: set DD RAM address

// cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


void lcd_gotoxy(unsigned char  ,unsigned char );

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcdData(unsigned char);
void lcdWriteNibble(unsigned char);
void waitlcd(unsigned char);
void prints(const char * message);
void lcd_clear(void);				//Clears LCD
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM

void integerToLcd(int  );
#endif
