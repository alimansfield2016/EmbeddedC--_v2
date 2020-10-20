#pragma once

#include <stdint.h>
#include <avr/util/util.hpp>
#include <avr/io/register.hpp>


constexpr AVR::Register8 PORTA(0x20);
constexpr AVR::Register8 DDRA(0x21);
constexpr AVR::Register8 PINA(0x22);

constexpr AVR::Register8 PORTB(0x23);
constexpr AVR::Register8 DDRB(0x24);
constexpr AVR::Register8 PINB(0x25);

constexpr AVR::Register8 PORTC(0x26);
constexpr AVR::Register8 DDRC(0x27);
constexpr AVR::Register8 PINC(0x28);

constexpr AVR::Register8 PORTD(0x29);
constexpr AVR::Register8 DDRD(0x2A);
constexpr AVR::Register8 PIND(0x2B);

constexpr AVR::Register8 UDR0(0xC6);
constexpr AVR::Register8 UBRR0H(0xC5);
constexpr AVR::Register8 UBRR0L(0xC4);
constexpr AVR::Register16 UBRR0(0xC4);
constexpr AVR::Register8 UCSR0A(0xC0);
constexpr AVR::Register8 UCSR0B(0xC1);
constexpr AVR::Register8 UCSR0C(0xC2);

constexpr AVR::Register8 SREG(0x5F);
constexpr uint8_t SREG_I = 0x07;

constexpr uint8_t USART0_RX_vect_num = 21;
constexpr uint8_t USART0_UDRE_vect_num = 22;
constexpr uint8_t USART0_TX_vect_num = 23;

constexpr uint8_t _VECTORS_COUNT = 31;

constexpr uint8_t WDP0 = 0;
constexpr uint8_t WDP1 = 1;
constexpr uint8_t WDP2 = 2;
constexpr uint8_t WDE = 3;
constexpr uint8_t WDCE = 4;
constexpr uint8_t WDP3 = 5;
constexpr uint8_t WDIE = 6;
constexpr uint8_t WDIF = 7;

constexpr AVR::Register8 WDTCSR(0x60);
constexpr AVR::Register8 EIFR(0x3C);
constexpr AVR::Register8 EIMSK(0x3D);
constexpr AVR::Register8 EICRA(0x69);
