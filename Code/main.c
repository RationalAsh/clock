#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"
//#include "I2C.h"
#include <string.h>
//#include "i2cmaster.h"
//#include "twimaster.c"
#define LED PB0
#define RTC 0x68
//#define RTC 0xD0

unsigned char* name        = "Ashwin";
unsigned char* greeting    = "Hello ";
unsigned char* compliment  = "You're awesome!";


int main()
{
    DDRB |= 0xFF; //Make all the pins output
    DDRC |= (1<<PC2)|(1<<PC3)|(1<<PC4);
    DDRD |= 0xFF;
    unsigned char msg[80] = "Hello Ashwin!";
    unsigned char time_s  = 0;
    
    //i2c_init();
    initLCD();
    writeAt(0, 0, greeting);
    writeString(name);
    writeString("!");
    writeAt(0, 2, compliment);
    //writeAt(0,1,msg1);
    /* gotoXY(10,2); */
    /* writeCom(0x94 + 0x0A); */

    //i2c_start_wait(RTC + I2C_WRITE);
    //i2c_write(0x00);
    //i2c_stop();

    //writeAt(10,2,"ABBA");
    //writeAt(11,2,"CC");

           
    while(1)
    {
        PORTB ^= (1<<LED);  //Toggle pin
	//i2c_start(RTC + I2C_READ);
	//time_s = i2c_readNak();
	//i2c_stop();

	//sprintf(msg, "%d", time_s);

	//writeAt(1,2,msg);
		
	_delay_ms(1000);
    }

    return 0;
}
