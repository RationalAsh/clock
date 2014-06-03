//Library for clocking
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

struct moment
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    unsigned char timeString[9];
    uint8_t second;
    unsigned char dateString[12];
} dflt = {14, 6, 3, 17, 10, "17:10:30", 30, "14- 6- 3"};


void updateTimeString(struct moment* m)
{
    //Update time string
    sprintf(m->timeString, "%2d:%2d:%2d", m->hour, m->minute, m->second);
}

void updateDateString(struct moment* m)
{
    sprintf(m->dateString, "%2d-%2d-%2d", m->year, m->month, m->day);
}

void updateAllStrings(struct moment* m)
{
    updateTimeString(m);
    updateDateString(m);
}

void tick(struct moment* m)
{
    m->second += 1;

    if(m->second == 60)
    {
	m->second  =  0;
	m->minute +=  1;
    }

    if(m->minute == 60)
    {
	m->minute  =  0;
	m->hour   +=  1;
    }

    if(m->hour == 24)
    {
	m->hour  = 0;
	m->day  += 1;
    }
}
