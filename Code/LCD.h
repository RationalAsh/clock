/*
 * LCD_Interfacing.c
 */
 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
 
#define dataPORT PORTD    	// In my case PORTB is the PORT from which I send data to my LCD
#define conPORT PORTC		// In my case PORTC is the PORT from which I set the RS , R/W and En
#define EN PORTC4		// Enable signal
#define RW PORTC3		// Read/Write signal
#define RS PORTC2		// Register Select signal

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
    writeCom(0x0F);
    writeCom(0x06);
    writeCom(0x01);
    writeCom(0x80);
}
    
