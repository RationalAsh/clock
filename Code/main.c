#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "I2C.h"
#include <string.h>
#define LED PB0

int main()
{
    DDRB |= 0xFF; //Make all the pins output
    DDRC |= (1<<PC2)|(1<<PC3)|(1<<PC4);
    DDRD |= 0xFF;
    unsigned char* msg = "Hello Word!";
  
    initLCD();
    writeString(msg);
    gotoXY(10,2);
    //writeCom(0x94 + 0x0A);
    writeAt(10,2,"ABBA");
           
    while(1)
    {
	PORTB ^= (1<<LED); //Toggle pin
	_delay_ms(2000);    //delay
    }

    return 0;
}
