#This is a makefile for the AVR code that runs the whole circuit
mcu=atmega8

final: main.o DTime.h LCD.h ADC.h
	avr-objcopy -j .text -j .data -O ihex main.o main.hex
main.o: main.c
	avr-gcc -mmcu=$(mcu) -Os main.c -o main.o
