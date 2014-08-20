/*
 * LCD_Interfacing.c
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

 
#define dataPORT PORTD    	// In my case PORTB is the PORT from which I send data to my LCD
#define conPORT PORTC		// In my case PORTC is the PORT from which I set the RS , R/W and En
#define EN PORTC3		// Enable signal
#define RW PORTC2		// Read/Write signal
#define RS PORTC1		// Register Select signal
#define line0 0x80
#define line1 0xC0
#define line2 0x94
#define line3 0xD4

//Delay function
void delay_ms(int ms)
{
    int i;
    for(i=0; i<ms; i++)
    {
	_delay_ms(1);
    }
}

//Function to write a command to the LCD command register.
//Send the command in as a hex number or whatever feels right to you.
void writeCom(unsigned char com)
{
    dataPORT = com;
    conPORT |= (1<<EN); //Set enable to high
    conPORT &= ~(1<<RS);
    conPORT &= ~(1<<RW);
    delay_ms(1);
    conPORT &= ~(1<<EN);
    delay_ms(1);
}

//Function to write a character to the LCD at the current cursor
//position. 
void writeChar(unsigned char ch)
{
    dataPORT = ch;
    conPORT |= (1<<EN)|(1<<RS); //Set enable to high
    conPORT &= ~(1<<RW);
    delay_ms(1);
    conPORT &= ~(1<<EN);
    delay_ms(1);
}

//This function initializes the LCD. This must be called
//before any of the other functions are used.
void initLCD()
{
    DDRC |= (1<<EN)|(1<<RS)|(1<<RW);
    writeCom(0x3C);
    writeCom(0x0C);
    writeCom(0x06);
    writeCom(0x01);
    writeCom(0x80);
}

//Writes a string to the LCD module starting at the current cursor position.
//The delay is the delay between writing each character on the screen. Put a
//delay of about 50ms for the best effect.
void writeString(unsigned char* msg, uint8_t delay)
{
    int i;
    for(i=0; i<strlen(msg); i++)
    {
	if(delay) delay_ms(delay);
	writeChar(msg[i]);
    }
}

//Makes the cursor go to an X,Y position on the 
//LCD. It's nice.
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
    
//Writes a string at a particular position on the LCD.
//Quite useful.
void writeAt(int X, int Y, unsigned char* msg, int delay)
{
    gotoXY(X,Y);
    if(strlen(msg) <= 20-X)
    {
	writeString(msg, delay);
    }
}
