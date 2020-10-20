
// #include <avr/interrupt/interrupt.hpp>
#include "avr/io/serial.hpp"
#include <avr/io/io.hpp>
// #include <avr/interrupt/watchdog.hpp>

#include <util/delay.h>


// #include <avr/memory/pgmspace.hpp>

// #include <libusb.hpp>


constexpr AVR::Serial serial({UDR0, UBRR0, UCSR0A, UCSR0B, UCSR0C}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});

/* 
void __vector_default (void){
	serial.PrintLn(AVR::pgm_ptr(PSTR("NO")));
} */
/* 
extern "C" void debug(const char* s) { 
	AVR::Interrupt::InterruptHolder hold;
	serial.PrintLn(AVR::pgm_ptr(s)); 
}
 */


int main(){
	// AVR::Interrupt::disable();

	// for(uint8_t s = 0; s; s++) _delay_ms(1);

	// _delay_ms(100);


	// const AVR::pgm_ptr str(PSTR("hello world"));
	// AVR::pgm_ptr timestr(PSTR(__TIME__));

	serial.begin(9600);

	for(uint32_t i = 0; i < 26; i++){
		serial.Print('A'+i);
	}

	serial.Print("Hello");
	// DDRB |= 0x80;


	// serial.PrintLn();
	serial.Print('H');
	// serial.Print('E');
	// serial.Print('L');
	// serial.Print('L');
	// serial.Print('O');
	// serial.Print('!');


	// AVR::USB::init();


	// AVR::Watchdog::setTimeoutCycles(AVR::Watchdog::TimeoutCycles::_1024K);
	// AVR::Watchdog::reset();

	// int ptr = (uint16_t)(str.ptr());

	// serial.PrintHex(ptr&0xFF);
	// serial.PrintHex(ptr>>8);




	while(true){
		// _delay_loop_2(1);
		// PORTB = 0x80;
		// PORTB = 0x80;
		// _delay_loop_2(1);
		// PORTB = ~0x80;
		// PORTB = ~0x80;

		// AVR::Watchdog::reset();
		// usbPoll();
		// serial.PrintLn(str);
		// serial.Print("b");
		// serial.Print('a');
	}
}
