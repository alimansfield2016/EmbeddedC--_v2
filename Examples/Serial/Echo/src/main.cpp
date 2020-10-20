/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR LibC++ Example Template Source

The source includes:

*/	

#define _AVR_IO_H_


#include <avr/io/io.hpp>
#include <avr/io/serial.hpp>
#include <avr/memory/pgmspace.hpp>
#include <avr/interrupt/watchdog.hpp>

constexpr AVR::Serial serial({UDR0, UBRR0, UCSR0A, UCSR0B, UCSR0C}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});

const char str2[] PROGMEM = "These strings are stored Exclusively in Program Memory.";
const char str3[] PROGMEM = "They are accessed by using the AVR::pgm_ptr class!";
const char backspc[] PROGMEM = "\x1b\x5b\x44 \x1b\x5b\x43";

int main()
{
	AVR::Watchdog::disable();
	AVR::Watchdog::setTimeoutCycles(AVR::Watchdog::TimeoutCycles::_256K);
	serial.begin(115200, true);

	serial.PrintLn(AVR::Serial::clr);

	serial.PrintLn(AVR::pgm_ptr(str2));
	serial.PrintLn(AVR::pgm_ptr(str3));

	while(true) {
		char c = serial.getChar();
		serial.Print(c);
		if(c == '\r') serial.Print('\n');
		if(c == '\b') serial.Print(AVR::pgm_ptr(backspc));
	}
}