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
			uint8_t txLenBuf[12];
			uint8_t &txLen;

			public:
			Endpoint0();
			
			virtual void setup(uint8_t *rxBuf, uint8_t &rxLen) override;
			virtual void out(uint8_t *rxBuf, uint8_t &rxLen) override;
			virtual void in() override;
		};
	} // namespace USB
	
} // namespace AVR
