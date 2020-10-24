/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR USB Endpoint Source

The source includes:

*/

#include <endpoint.hpp>
#include "endpoint0.hpp"
#include "usbdrv.h"
#include "libusb_ext.hpp"

using namespace AVR::USB;

Endpoint0 _endp0{};
Endpoint *AVR::USB::endp0{&_endp0};

void Endpoint::setup(uint8_t *rxBuf, uint8_t &rxLen)
{
	rxLen = 0;
}
void Endpoint::out(uint8_t *rxBuf, uint8_t &rxLen)
{
	rxLen = 0;
}
void Endpoint::in()
{
	//prepare buffer for next transfer if required
}

Endpoint0::Endpoint0()
{
	// usbTxBufs[0] = txBuf;
	// usbTxLens[0] = &txLen;
}

void Endpoint0::setup(uint8_t *rxBuf, uint8_t &rxLen)
{
	if(rxLen < 8)
	{
		rxLen = 0;
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
		if(request == Request::SetAddress){
			usbNewDeviceAddr = wValue&0x7F;
			return;
		}else if(request == Request::GetStatus){

		}
	case RequestType::Class :
	case RequestType::Vendor :
		/* code */
		break;
	}

	// txBuf[0] = 0xa5;
	// txLen = 1;
}

void Endpoint0::in()
{

}

void Endpoint0::out(uint8_t *rxBuf, uint8_t &rxLen)
{

}