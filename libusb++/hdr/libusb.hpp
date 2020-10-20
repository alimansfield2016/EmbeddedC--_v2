#pragma once

/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR LibUSB++ Header

The <libusb.hpp> header includes:
- DeviceConfiguration
- Interface
*/


namespace AVR
{
	namespace USB
	{
		class Descriptor;
		class StringDescriptor;
		class Device;
		class DeviceConfiguration;
		class InterfaceConfiguration;
		class Interface;
		class Endpoint;
		class EndpointIn;
		class EndpointOut;



		/* {
			extern void __attribute__((used, signal, externally_visible)) __vector_3();
			//variables defined by our c/asm implementation
		} */

		/**
		 * Initialise the USB connection
		 * This includes enabling the relevant interrupts
		 */
		void init();
		void reset();
	} // namespace USB
	
} // namespace AVR

#include "endpoint.hpp"
