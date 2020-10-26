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
		class Endpoint0;
		extern Endpoint0 _endp0;
		class Endpoint0 : public Endpoint
		{
			//state to hold whatever we're doing since we can't output everything at once, its all async
			public:
			Endpoint0();
			
			void setup(uint8_t *rxBuf, uint8_t &rxLen) override;
			void out(uint8_t *rxBuf, uint8_t &rxLen) override;
			void in() override;

			void getDeviceStatus();
			void getDescriptor(DescriptorType type, uint8_t idx);
			void setDeviceAddress(uint8_t addr);
		};
	} // namespace USB
	
} // namespace AVR
