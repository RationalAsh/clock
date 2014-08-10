//Library for clocking
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define DEC 10
#define MIL 2000

struct moment
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    unsigned char timeString[9];
    uint8_t second;
    unsigned char dateString[11];
    uint8_t daysInMonth[13];
    unsigned char *dayString;
} dflt = {14, 12, 31, 23, 59, "23:59:55", 55, "14-12-31", 
	  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

unsigned char *getDay(int year, int month, int day) {
  static unsigned char *weekdayname[] = {"MON", "TUE",
        "WED", "THU", "FRI", "SAT", "SUN"};
  int32_t JND =                                                    \
          day                                                      \
        + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5) \
        + (365 * (year + 4800 - ((14 - month) / 12)))              \
        + ((year + 4800 - ((14 - month) / 12)) / 4)                \
        - ((year + 4800 - ((14 - month) / 12)) / 100)              \
        + ((year + 4800 - ((14 - month) / 12)) / 400)              \
        - 32045;
  return weekdayname[(JND+3) % 7];
}

unsigned char *getDay2(int year, int month, int day) {
  /* using C99 compound literals in a single line: notice the splicing */
  return ((unsigned char *[])                                      \
          {"MON", "TUE", "WED",                                    \
           "THU", "FRI", "SAT", "SUN"})[                           \
      (                                                            \
          day                                                      \
        + ((153 * (month + 12 * ((14 - month) / 12) - 3) + 2) / 5) \
        + (365 * (year + 4800 - ((14 - month) / 12)))              \
        + ((year + 4800 - ((14 - month) / 12)) / 4)                \
        - ((year + 4800 - ((14 - month) / 12)) / 100)              \
        + ((year + 4800 - ((14 - month) / 12)) / 400)              \
        - 32045                                                    \
      ) % 7];
}

void pushIntToStr(int i, unsigned char* str, int startPos, int numberOfDigits)
{
    unsigned char* tmp;
    int j;
    tmp = (unsigned char*) malloc(numberOfDigits);

    itoa(i, tmp, DEC);
    for(j=0; j<numberOfDigits; j++)
    {
	if(i < 10)
	{
	    str[startPos] = '0';
	    str[startPos+1] = tmp[0];
	}
	else
	{
	    str[j+startPos] = tmp[j];
	}
    }
    free(tmp);
}

void updateTimeString(struct moment* m)
{
    pushIntToStr(m->hour, m->timeString, 0, 2);
    m->timeString[2] = ':';
    pushIntToStr(m->minute, m->timeString, 3, 2);
    m->timeString[5] = ':';
    pushIntToStr(m->second, m->timeString, 6, 2);
}

void updateDateString(struct moment* m)
{
    pushIntToStr(m->year+MIL, m->dateString, 0, 4);
    m->dateString[4] = '-';
    pushIntToStr(m->month, m->dateString, 5, 2);
    m->dateString[7] = '-';
    pushIntToStr(m->day, m->dateString, 8, 2);
    m->dayString = getDay(m->year, m->month, m->day);
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

    if(m->day > m->daysInMonth[m->month])
    {
	m->day     = 1;
	m->month  += 1;
    }
    
    if(m->month > 12)
    {
	m->month  = 1;
	m->year  += 1;
    }
}
