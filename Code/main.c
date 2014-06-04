#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"
#include "DTime.h"
#include <avr/pgmspace.h>


#define LCD_TEXT_DELAY 50
#define NO_DELAY 0


int main()
{
    //Message strings for the LCD
    unsigned char* greeting   = {"Hello Ashwin!"};
    unsigned char* compliment = {"You're awesome!"};
    struct moment time;
    DDRB |= 0xFF; //Make all the pins output
    DDRD |= 0xFF;
    time = dflt;  //Initialize struct to default values
        
    initLCD();
    writeAt(0, 1, time.timeString, LCD_TEXT_DELAY);
    writeAt(0, 2, greeting, LCD_TEXT_DELAY);
    writeAt(0, 3, compliment, LCD_TEXT_DELAY);
    _delay_ms(3000);
           
    while(1)
    {
	tick(&time);
	updateAllStrings(&time);
	writeAt(0, 0, time.dateString, NO_DELAY);
	writeAt(0, 1, time.timeString, NO_DELAY);
	writeAt(16, 0, time.dayString, NO_DELAY);
	_delay_ms(1000);
    }

    return 0;
}
