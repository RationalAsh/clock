#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"
#include "DTime.h"
#include <avr/pgmspace.h>

#define LCD_TEXT_DELAY 50
#define NO_DELAY 0
#define LM34 PC0
#define SET PB0
#define UP PB1
#define DWN PB2

//Get temperature reading
int getTemp();

int main()
{
    //Message strings for the LCD
    unsigned char* greeting   = {"Hello Aurora!"};
    unsigned char* compliment = {"You're awesome!"};
    unsigned char* temp = {"39"};
    unsigned char* units = {"dC"};
    units[0] = (char)223;
    //uint16_t temp_adc;
    struct moment time;
    DDRB |= 0xFF; //Make all the pins output
    DDRD |= 0xFF;
    time = dflt;  //Initialize struct to default values

       
    
    initLCD();
    writeAt(0, 1, time.timeString, LCD_TEXT_DELAY);
    writeAt(0, 2, greeting, LCD_TEXT_DELAY);
    writeAt(0, 3, compliment, LCD_TEXT_DELAY);
    writeAt(18, 1, units, NO_DELAY);
    _delay_ms(3000);
           
    while(1)
    {
	tick(&time);

	updateAllStrings(&time);
	writeAt(0, 0, time.dateString, NO_DELAY);
	writeAt(0, 1, time.timeString, NO_DELAY);
	writeAt(17, 0, time.dayString, NO_DELAY);
	//temp_adc = (5 * getTemp() * 100)/1024;
	itoa((5 * getTemp() * 100)/1024, temp, DEC);
	writeAt(16, 1, temp, NO_DELAY);
        //writeAt(17, 1, "°C", NO_DELAY); 
	_delay_ms(1000);
    }

    return 0;
}

int getTemp()
{
    //Enable the ADC
    ADCSRA |= (1<<ADEN);
    //8Bit precision
    //ADMUX |= (1<<ADLAR);
    //AREF
    ADMUX &= ~((1<<REFS0)|(1<<REFS1)|(1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));
    //Select ADC0
    //ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));

    //Start conversion
    ADCSRA |= (1<<ADSC);
    //Wait for the conversion to complete
    _delay_us(1);
    //Read the ADC in 10 bit resolution
    return ADCL + (ADCH<<8);
}
