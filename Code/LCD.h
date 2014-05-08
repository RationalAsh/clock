/*
 * LCD_Interfacing.c
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define dataPORT PORTD    	// In my case PORTB is the PORT from which I send data to my LCD
#define conPORT PORTC		// In my case PORTC is the PORT from which I set the RS , R/W and En
#define EN PORTC4		// Enable signal
#define RW PORTC3		// Read/Write signal
#define RS PORTC2		// Register Select signal
#define line0 0x80
#define line1 0xC0
#define line2 0x94
#define line3 0xD4

void writeCom(unsigned char com)
{
    dataPORT = com;
    conPORT |= (1<<EN); //Set enable to high
    conPORT &= ~(1<<RS);
    conPORT &= ~(1<<RW);
    _delay_ms(1);
    conPORT &= ~(1<<EN);
    _delay_ms(1);
}

void writeChar(unsigned char ch)
{
    dataPORT = ch;
    conPORT |= (1<<EN)|(1<<RS); //Set enable to high
    conPORT &= ~(1<<RW);
    _delay_ms(1);
    conPORT &= ~(1<<EN);
    _delay_ms(1);
}

void initLCD()
{
    writeCom(0x3C);
    writeCom(0x0C);
    writeCom(0x06);
    writeCom(0x01);
    writeCom(0x80);
}

void writeString(unsigned char* msg)
{
    int len = strlen(msg);
    int i = 0;
    for(i=0; i<len; i++)
    {
	writeChar(msg[i]);
    }
}

void gotoXY(int X, int Y)
{
    int com = 0x00;
    switch(Y)
    {
    case 0:
	com = line0 + X;
	break;
    case 1:
	com = line1 + X;
	break;
    case 2:
	com = line2 + X;
	break;
    case 3:
	com = line3 + X;
	break;
    }

    writeCom(com);
}
    
void writeAt(int X, int Y, unsigned char* msg)
{
    gotoXY(X,Y);
    int len = strlen(msg);
    if(len < 20-X)
    {
	writeString(msg);
    }
}
