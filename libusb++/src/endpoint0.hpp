#pragma once

/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR USB Endpoint0 Header

The <> header includes:

*/

#include <endpoint.hpp>

namespace AVR
{
	namespace USB
	{
		class Endpoint0 : public Endpoint
		{
			
			virtual void setup(uint8_t *rxBuf, uint8_t &rxLen) override;
			virtual void out(uint8_t *rxBuf, uint8_t &rxLen) override;
			virtual void in(uint8_t *txBuf) override;
		};
	} // namespace USB
	
} // namespace AVR
