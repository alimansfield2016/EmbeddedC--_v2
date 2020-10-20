
#include <avr/interrupt/interrupt.hpp>
#include "avr/io/serial.hpp"
#include <avr/io/io.hpp>
// #include <avr/memory/pgmspace.hpp>


#include <memory>
#include <bits/c++allocator.hpp>

#include <new>

constexpr AVR::Serial serial({UDR0, UBRR0, UCSR0A, UCSR0B, UCSR0C}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});
// const char* PROGMEM s = "Hello World!";
// AVR::pgm_ptr<char> hw_str(s);



int tri(int t){
	int sum = 0;
	while(t){
		sum += t--;
	}
	return sum;
}

int main(){

	serial.PrintLn("hello world");

	std::unique_ptr intptr(new int(3));

	bool led = false;

	DDRB |= 0x80;

	while(true){
		for(uint32_t counter = 0; counter; counter++);
		led = !led;
		PORTB ^= 0x80;
	}
}
