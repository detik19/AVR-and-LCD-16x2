#ifndef __lcd16_h_
#define __lcd16_h_


#include <avr/io.h>


#define RS  0x01
#define EN  0x04
#define RW  0x02
void gotoXy(unsigned char  ,unsigned char );
void lcdInit(void);
void lcdCmd(unsigned char);
void lcdData(unsigned char);
void lcdWriteNibble(unsigned char);
void waitlcd(unsigned char);
void prints(const char * message);

void integerToLcd(int  );
#endif
