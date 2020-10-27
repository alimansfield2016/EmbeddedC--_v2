/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR LibUSB++ Source

The source includes:

*/

#include <libusb.hpp>
#include <avr/io/io.hpp>
#include <avr/interrupt/interrupt.hpp>
#include <avr/interrupt/watchdog.hpp>
#include <util/delay.h>
#include "libusb_ext.hpp"

#include <avr/interrupt.h>

#include "endpoint0.hpp"

extern void* operator new(size_t, void*);

volatile uint8_t* usbTxLenBufs[16] = {0};



void AVR::USB::init()
{
	//initialise USB here
	AVR::USB::reset();

	USB_INTR_CFG = USB_INTR_CFG_SET;
	USB_INTR_ENABLE = 1<<USB_INTR_ENABLE_BIT;
	USB_INTR_PENDING = 1<<USB_INTR_PENDING_BIT;

	PORTB |= 0x03;
	DDRB |= 0x01;

	usbDeviceAddr = 0;
	usbNewDeviceAddr = 0;
	usbRxLen = 0;
	usbTransactionEnd = 0;

	endp0 = &_endp0;

	AVR::Interrupt::enable();
}

void AVR::USB::reset()
{
	AVR::Interrupt::InterruptHolder hold;
	DDRB |= 0x0C;
	PORTB &= ~0x0C;

	uint8_t i = 0;
	while(--i){
		AVR::Watchdog::reset();
		_delay_ms(1);
	}
	DDRB &= ~0x0C;
}

void __attribute__((interrupt)) handleTransaction()
{
	PORTB &= ~0x01;

	// PORTB |= 0x01;
	// return;
	//Interrupts have already been re-enabled
	//in the assembly call to this function

	//process data input
	//this function is called for Setup and Out transactions
	switch (usbEndptNo)
	{
	case 0:
		if(usbRxToken == USBPID_SETUP)
			AVR::USB::endp0->setup(usbRxBuf, usbRxLen);
			// AVR::USB::_endp0.setup(usbRxBuf, usbRxLen);
		break;
	
	default:
		break;
	}
	PORTB |= 0x03;
}