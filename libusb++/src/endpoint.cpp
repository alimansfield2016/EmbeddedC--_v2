/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR USB Endpoint Source

The source includes:

*/

#include <endpoint.hpp>
#include "endpoint0.hpp"
#include "libusb_ext.hpp"
extern "C"{
	#include "usbdrv.h"
}

using namespace AVR::USB;

Endpoint0 _endp0{};
Endpoint *AVR::USB::endp0{&_endp0};

Endpoint::Endpoint() : txLen(txLenBuf[0]), txBuf(&txLenBuf[1])
{

}

void Endpoint::setup(uint8_t *rxBuf, uint8_t &rxLen)
{
	PINB = 0x01;
	rxLen = 0;
}
void Endpoint::out(uint8_t *rxBuf, uint8_t &rxLen)
{
	rxLen = 0;
}
void Endpoint::in()
{
	txLen = 0;
	//prepare buffer for next transfer if required
}

void Endpoint::genCRC16()
{
	usbCrc16Append(txBuf+1, txLen-1);
	txLen += 2;


	// constexpr uint16_t poly = 0x8005;
	// //set CRC bytes to 0
	// txBuf[txLen++] = 0;
	// txBuf[txLen++] = 0;

	// bool carryLow, carryHigh;
	// uint16_t r = txBuf[0]<<8 | txBuf[1];
	// uint8_t s = txBuf[2];

	// for(uint8_t i = 3; i <= txLen; i++){
	// 	for(uint8_t b = 0; b < 8; b++){
	// 		carryHigh = r&0x8000;
	// 		carryLow = s&0x80;
	// 		s<<=1;
	// 		r<<=1;
	// 		if(carryLow) r |= 0x01;
	// 		if(carryHigh)
	// 			r ^= poly;
	// 	}
	// 	s = txBuf[i];
	// }


}

Endpoint0::Endpoint0()
{
	usbTxLenBufs[0] = txLenBuf;
	txLen = 0;

	txBuf[0] = USBPID_DATA1;
	txLen = 1;
	genCRC16();	
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
	txLen = 4;
	txBuf[0] = 0x00;
	txBuf[1] = 0x00;
	txBuf[2] = 0x00;
	txBuf[3] = 0x00;
}

void Endpoint0::setDeviceAddress(uint8_t addr)
{
	PINB = 0x02;
	usbNewDeviceAddr = addr;
	txBuf[0] = USBPID_DATA1;
	txBuf[1] = 0;
	txBuf[2] = 0;
	txLen = 3;
}
