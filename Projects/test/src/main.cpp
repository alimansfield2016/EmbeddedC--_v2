
#define ENABLE_INTERRUPTS

#include <avr/io/ports.hpp>
#include <avr/io/pin.hpp>
#include <avr/io/serial.hpp>
#include <avr/io/twi.hpp>
#include <avr/io.h>
#include <avr/interrupt/interrupt.hpp>
#include <util/delay.h>

// #include <3PT/RTC_MCP7940M/MCP7940M.hpp>
#include <3PT/DustSensor_SM-UART-04L/SM-UART-04L.hpp>

#define RTC_ADDR 0x6F

constexpr const AVR::Port LedPort = AVR::Ports::PortB;

// constexpr AVR::Serial Serial({REG(UDR0), (intptr_t)(&UBRR0), (intptr_t)(&UCSR0A), (intptr_t)(&UCSR0B), (intptr_t)(&UCSR0C)}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});
constexpr AVR::Serial Serial({UDR0, UBRR0, UCSR0A, UCSR0B, UCSR0C}, {USART0_RX_vect_num, USART0_UDRE_vect_num, USART0_TX_vect_num});
constexpr AVR::Serial Serial1({UDR1, UBRR1, UCSR1A, UCSR1B, UCSR1C}, {USART1_RX_vect_num, USART1_UDRE_vect_num, USART1_TX_vect_num});
constexpr AVR::TWI TWI({(intptr_t)(&TWBR), (intptr_t)(&TWCR), (intptr_t)(&TWSR), (intptr_t)(&TWDR), (intptr_t)(&TWAR), (intptr_t)(&TWAMR)});

constexpr AVR::Pin scl(AVR::Ports::PortC, 0), sda(AVR::Ports::PortC, 1);

// constexpr AVR::Ext::RTC_MCP7940M RTC(TWI);
AVR::Ext::DustSensor ds(Serial1);

void echo()
{
	Serial.PrintHex(Serial1.getChar());
}

void setup()
{
	Serial.begin(115200);
	Serial.PrintLn("\033[2J");
	Serial.PrintLn("Hello World");

	Serial1.begin(9600);
	Serial1.registerHandler(echo, AVR::Serial::Interrupt::rx);

	AVR::Interrupt::enable();
	Serial1.rxc_int_enable();

	ds.send(AVR::Ext::DustSensor::cmd::GetReading);

	LedPort.ddr() |= 0xFF;
	LedPort.port() |= 0xFF;

	//424D 001C 03E7 03E7 03E7 03E7 03E7 03E7 0000 0000 0000 0000 0000 0000 0C00 0633

	// uint8_t cmd = 0xE2;
	// uint16_t data = 0x0000;

	// Serial1.Print("\x42\x4D");
	// Serial1.Print(cmd);
	// Serial1.Print(data >> 8);
	// Serial1.Print(data & 0xFF);
	// uint16_t crc = 0x42 + 0x4D + cmd + (data >> 8) + (data & 0xFF);
	// Serial1.Print(crc >> 8);
	// Serial1.Print(crc & 0xFF);

	// scl.direction(false);
	// sda.direction(false);
	// scl = 1;
	// sda = 1;

	// TWI.init_master(100000);

	// TWI.scan([](uint8_t addr) {Serial.Print("Device found at addr : 0x"); Serial.PrintHex(addr); Serial.PrintLn(); });

	// if (false)
	// {
	// 	RTC.setCompiledDateTime();
	// 	// AVR::TWITransmission tx(TWI, RTC_ADDR);
	// 	// tx
	// 	// 	.write(0x00) //addr
	// 	// 	.write(0x80) //seconds
	// 	// 	.write(0x34)
	// 	// 	.write(0x43);
	// }
}

void loop()
{
	// dump_rtc(0x10);
	// Serial.Print("\r");
	// Serial.Print(RTC.timeStr());

	_delay_ms(1000);
}

int main()
{
	setup();

	while (true)
		loop();
}