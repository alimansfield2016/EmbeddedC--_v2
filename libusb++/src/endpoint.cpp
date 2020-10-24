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

Endpoint0::Endpoint0() : txLen(txLenBuf[0])
{
	usbTxLenBufs[0] = txLenBuf;
	txLenBuf[1+0] = USBPID_DATA1;
	txLenBuf[1+1] = 18;
	txLenBuf[1+2] = 1;
	txLenBuf[1+3] = 0x10;
	txLenBuf[1+4] = 0x01;
	txLenBuf[1+5] = 0xFF;
	txLenBuf[1+6] = 0x00;
	txLenBuf[1+7] = 0x00;
	txLenBuf[1+8] = 0x08;
	txLenBuf[1+9] = 0x21;
	txLenBuf[1+10] = 0x63;


	txLen = 11;
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

}

void Endpoint0::in()
{

}

void Endpoint0::out(uint8_t *rxBuf, uint8_t &rxLen)
{

}