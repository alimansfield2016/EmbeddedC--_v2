/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR USB Endpoint0 Source

The source includes:

*/

#include <endpoint.hpp>
#include "endpoint0.hpp"
#include "libusb_ext.hpp"
extern "C"{
	#include "usbdrv.h"
}

using namespace AVR::USB;

Endpoint0 AVR::USB::_endp0{};
Endpoint *AVR::USB::endp0;


Endpoint0::Endpoint0()
{
	DDRB |= 0x02;
	PORTB |= 0x02;
	PORTB &= ~0x02;

	usbTxLenBufs[0] = txLenBuf;
	txLen = 0;

	txBuf[0] = USBPID_DATA1;
	txLen = 1;
	genCRC16();	
}

void Endpoint0::setup(uint8_t *rxBuf, uint8_t &rxLen)
{
	PORTB &= ~0x02;
	if(rxLen < 8)
	{
		rxLen = 0;
		PORTB |= 0x02;
		return;
	}

	uint8_t bmRequestType = *rxBuf++;
	uint8_t bRequest = *rxBuf++;
	uint16_t wValue = *rxBuf++ << 8; wValue = *rxBuf++;
	uint16_t wIndex = *rxBuf++ << 8; wIndex = *rxBuf++;
	uint16_t wCount = *rxBuf++ << 8; wCount = *rxBuf++;
	rxLen = 0;

	RequestDirection direction = static_cast<RequestDirection>(bmRequestType>>7);
	RequestRecipient recipient = static_cast<RequestRecipient>(bmRequestType&0x1F);
	RequestType type = static_cast<RequestType>((bmRequestType>>5)&0x03);

	Request request = static_cast<Request>(bRequest);

	switch (type)
	{
	case RequestType::Standard :
		if(request == Request::SetAddress)
			setDeviceAddress(wValue&0x7F);
		else if(request == Request::GetStatus)
			getDeviceStatus();
		else if(request == Request::GetDescriptor){
			DescriptorType descType = static_cast<DescriptorType>(wValue>>8);
			uint8_t descIdx = static_cast<uint8_t>(wValue);
			getDescriptor(descType, descIdx);
		}
		break;		
	case RequestType::Class :
		break;
	case RequestType::Vendor :
		/* code */
		break;
	}
	PORTB |= 0x02;

}

void Endpoint0::in()
{
	txLen = 0;
}

void Endpoint0::out(uint8_t *rxBuf, uint8_t &rxLen)
{

}

void Endpoint0::getDeviceStatus()
{
	txBuf[0] = 0x00;
	txBuf[1] = 0x00;
	txBuf[2] = 0x00;
	txBuf[3] = 0x00;
	txLen = 4;
	genCRC16();
}

void Endpoint0::getDescriptor(DescriptorType type, uint8_t idx)
{
	switch (type)
	{
	case DescriptorType::Device :
	case DescriptorType::Configuration :
	case DescriptorType::Interface :
	case DescriptorType::Endpoint :
	case DescriptorType::String :
		/* code */
		break;
	}
}

void Endpoint0::setDeviceAddress(uint8_t addr)
{
	usbNewDeviceAddr = addr;
	txBuf[0] = USBPID_DATA1;
	txLen = 1;
	genCRC16();
}
