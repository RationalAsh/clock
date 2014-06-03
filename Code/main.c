#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"
#include <string.h>
#include "i2chw/twimaster.c"

#define LED PB0
#define RTC 0x68
#define LCD_TEXT_DELAY 50

//Message strings for the LCD
unsigned char* name        = "Ashwin";
unsigned char* greeting    = "Hello ";
unsigned char* compliment  = "You're awesome!";
uint8_t year;
uint8_t month;
uint8_t day;
uint8_t hour;
uint8_t minute;
uint8_t second; 


int main()
{
    DDRB |= 0xFF; //Make all the pins output
    DDRC |= (1<<PC2)|(1<<PC3)|(1<<PC4);
    DDRD |= 0xFF;
    unsigned char msg[80] = "Hello Ashwin!";
    unsigned char time_s  = 0;
    int counter = 0;
    unsigned char *cnt = "000";
    
    initLCD();
    ds1307_init();
    writeAt(0, 0, greeting, LCD_TEXT_DELAY);
    writeString(name, LCD_TEXT_DELAY);
    writeString("!", 0);
    writeAt(0, 2, compliment, LCD_TEXT_DELAY);
    _delay_ms(3000);

           
    while(1)
    {
        PORTB ^= (1<<LED);  //Toggle pin
	sprintf(cnt, "%d", counter);
	writeAt(0, 3, cnt, 0);

	ds1307_getdate(&year, &month, &day, &hour, &minute, &second);
	
	_delay_ms(1000);
	counter++;
    }

    return 0;
}
