#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"
#include "DTime.h"
//#include <avr/pgmspace.h>
#include <avr/interrupt.h>


#define LCD_TEXT_DELAY 50
#define NO_DELAY 0
#define LM34 PC0
#define SET  PB0
#define UP   PB1
#define DWN  PB2
#define MODE PB3

struct moment time;
unsigned char* cnt = "0";
uint8_t setFlag = 0;
uint8_t setMode = 0;
//Message strings for the LCD

//unsigned char* nick1      = {"Tibha!"};

//unsigned char* morning    = {"Good Morning "};

unsigned char* temp       = {"39"};
unsigned char* units      = {"dC"};


//Get temperature reading
int getTemp();
void startClock();

int main()
{

    units[0] = (char)223;
    char modes[] = "smhDMY";
	char mode[] = "MODE:  ";
    
    //uint16_t temp_adc;
    
    DDRB |= 0xFF; //Make all the pins output
    DDRB &= ~((1<<SET)|(1<<UP)|(1<<DWN));
    //Enabling the internal pullup resistors
    PORTB |= (1<<SET)|(1<<UP)|(1<<DWN);
    DDRD |= 0xFF;
    time = dflt;  //Initialize struct to default values

       
    //Initialize the LCD
    initLCD();
        
    //writeAt(0, 1, morning, LCD_TEXT_DELAY);
    //writeAt(0, 13, nick1, LCD_TEXT_DELAY);
    writeAt(18, 0, units, NO_DELAY);
    //writeAt(0, 3, "MODE: ", NO_DELAY);
    _delay_ms(3000);
    startClock();
    //enable global interrupts
    sei();
           
    while(1)
    {
	if(!(PINB &(1<<SET))&&(setFlag))
	{
	    setMode++;
	    if(setMode>6) setMode = 0;
	    setFlag = 0;
	    mode[6] = modes[setMode];
	    writeAt(6, 3, mode, NO_DELAY);
	}
	if(!(PINB & (1<<SET)))
	{
	    setFlag = 1;
	}

	if(!(PINB &(1<<UP)))
	{
	    switch(setMode)
	    {
	    case 0:
		time.second++;
		break;
	    case 1:
		time.minute++;
		break;
	    case 2:
		time.hour++;
		break;
	    case 3:
		time.day++;
		break;
	    case 4:
		time.month++;
		break;
	    case 5:
		time.year++;
		break;
	    }
	}

	if(!(PINB &(1<<DWN)))
	{
	    switch(setMode)
	    {
	    case 0:
		time.second--;
		break;
	    case 1:
		time.minute--;
		break;
	    case 2:
		time.hour--;
		break;
	    case 3:
		time.day--;
		break;
	    case 4:
		time.month--;
		break;
	    case 5:
		time.year--;
		break;
	    }
	}

	//Start conversion (ADC
	ADCSRA |= (1<<ADSC);
	delay_ms(500);
	//_delay_ms(500);
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
    //while(!(ADCSRA & (1<<ADIF)))
    _delay_us(1);
    //asm("nop");
    //Read the ADC in 10 bit resolution
    return ADC;
}

void startClock()
{
    //Set mode of operation CTC with OCR1A
    TCCR1A &= ~((1<<WGM11)|(1<<WGM10));
    TCCR1B |= (1<<WGM12)|(1<<CS10)|(1<<CS11);
    TCCR1B &= ~((1<<WGM13)|(1<<CS12));
    //Set the compare match value
    OCR1A = 15625;
    //Enable the interrupt
    TIMSK |= (1<<OCIE1A);
    //Set clock prescaler 1/64
    //TCCR1B |= (1<<CS10)|(1<<CS11);
    //TCCR1B &= ~(1<<CS12);
}

ISR(TIMER1_COMPA_vect)
{
    tick(&time);
    updateAllStrings(&time);
    writeAt(0, 0, time.dateString, NO_DELAY);
    writeAt(6, 2, time.timeString, NO_DELAY);
    writeAt(11, 0, time.dayString, NO_DELAY);
    itoa((5 * getTemp() * 100)/1024, temp, DEC);
    writeAt(16, 0, temp, NO_DELAY);
}
    
    
    
