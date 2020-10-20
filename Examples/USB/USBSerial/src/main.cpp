#include <libusb.hpp>

#include <avr/interrupt/watchdog.hpp>
// #include <avr/io/serial.hpp>
#include <avr/io/io.hpp>

#include <new>

#include <util/delay.h>


// constexpr AVR::Serial serial({UDR0, UBRR0, UCSR0A, UCSR0B, UCSR0C}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});

// const char time[] PROGMEM = __TIME__;
// const char dbgstr[] PROGMEM = "Debugging uart";
// const char usbinitstr[] PROGMEM = "Initialising USB";
// const char filler[] PROGMEM = "filler";
// const char _clr[] PROGMEM = "\033[2J";


int main(){
	AVR::Watchdog::setMode(AVR::Watchdog::Mode::Stopped);

	// _delay_ms(1000);

	// serial.begin(1200);

	// serial.PrintLn(AVR::pgm_ptr<char>(_clr));
	// serial.PrintLn(AVR::pgm_ptr<char>(time));
	// serial.PrintLn(AVR::pgm_ptr<char>(dbgstr));




	// serial.PrintLn(AVR::pgm_ptr<char>(usbinitstr));


	AVR::USB::init();
	AVR::Interrupt::enable();
	EIMSK |= 1<<2;
	EICRA |= 0x30;
	EIFR = 1<<2;
	// AVR::USB::reset();


	uint8_t i = 0;

	while(++i) {
		_delay_ms(500);
		if(i) i--;
		// serial.PrintHex(i);
		// serial.PrintLn();
	}

	// serial.PrintLn();


}