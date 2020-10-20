#pragma once

#include <avr/io/serial.hpp>
#include <avr/io.h>

constexpr AVR::Serial Serial({(intptr_t)(&UDR0), (intptr_t)(&UBRR0), (intptr_t)(&UCSR0A), (intptr_t)(&UCSR0B), (intptr_t)(&UCSR0C)});
