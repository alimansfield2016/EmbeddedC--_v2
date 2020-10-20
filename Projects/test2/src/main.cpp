
#define ENABLE_INTERRUPTS

#include <avr/io/ports.hpp>
#include <avr/io/serial.hpp>
#include <util/delay.h>

#define RTC_ADDR 0x6F

constexpr const AVR::Port LedPort = AVR::Ports::PortB;

extern uint8_t udr0;
extern uint16_t ubrr0;
extern uint8_t ucsr0a;
extern uint8_t ucsr0b;
extern uint8_t ucsr0c;

constexpr AVR::Serial Serial({udr0, ubrr0, ucsr0a, ucsr0b, ucsr0c}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});

void setup()
{
	Serial.begin(115200);
	Serial.PrintLn("\033[2J");
	Serial.PrintLn("Hello World");
}

void loop()
{

	_delay_ms(1000);
}

int main()
{
	setup();

	while (true)
		loop();
}