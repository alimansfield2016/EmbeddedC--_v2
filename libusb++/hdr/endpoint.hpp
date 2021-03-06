#pragma once

/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR USB Endpoint Source

The source includes:

*/

#include <stdint.h>

namespace AVR
{
	namespace USB
	{
		class Endpoint;
		extern Endpoint *endp0;

		enum class RequestType
		{
			Standard = 0,
			Class = 1,
			Vendor = 2,
		};

		enum class RequestRecipient
		{
			Device = 0,
			Interface = 1,
			Endpoint = 2,
			Other = 3,
		};

		enum class RequestDirection : bool
		{
			HostToDevice = false,
			DeviceToHost = true,
		};

		enum class Request
		{
			GetStatus = 0,
			ClearFeature = 1,
			SetFeature = 3,
			SetAddress = 5,
			GetDescriptor = 6,
			SetDescriptor = 7,
			GetConfiguration = 8,
			SetConfiguration = 9,
			GetInterface = 10,
			setInterface = 11,
			SynchFrame = 18,
		};

		enum class DescriptorType
		{
			Device = 1,
			Configuration = 2,
			String = 3,
			Interface = 4,
			Endpoint = 5,
		};

		class Endpoint
		{
			friend class Endpoint0;
			private:
			volatile uint8_t txLenBuf[12];
			protected:
			volatile uint8_t *const txBuf;
			volatile uint8_t &txLen;

			void genCRC16();
			
			public:

			Endpoint();

			virtual void setup(uint8_t *rxBuf, uint8_t &rxLen);
			virtual void out(uint8_t *rxBuf, uint8_t &rxLen);
			virtual void in();
		};

	} // namespace USB
	
} // namespace AVR
