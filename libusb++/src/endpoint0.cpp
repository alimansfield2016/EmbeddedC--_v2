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
Endpoint *AVR::USB::endp0{&_endp0};


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
		return;
	}
	++rxBuf;
	uint8_t bmRequestType = *rxBuf++;
	uint8_t bRequest = *rxBuf++;
	uint16_t wValue = *rxBuf++; wValue |= *rxBuf++ << 8;
	uint16_t wIndex = *rxBuf++; wIndex |= *rxBuf++ << 8;
	uint16_t wCount = *rxBuf++; wCount |= *rxBuf++ << 8;
	rxLen = 0;

	RequestDirection direction = static_cast<RequestDirection>(bmRequestType>>7);
	RequestRecipient recipient = static_cast<RequestRecipient>(bmRequestType&0x1F);
	RequestType type = static_cast<RequestType>((bmRequestType>>5)&0x03);

	Request request = static_cast<Request>(bRequest);

	PINB = 0x01;
	PINB = 0x01;
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
		PINB = 0x02;
		PINB = 0x02;
		break;		
	case RequestType::Class :
		break;
	case RequestType::Vendor :
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
	constexpr uint16_t bcdUSB = 0x0110;
	constexpr uint16_t idVendor = 0;
	constexpr uint16_t idProduct = 0;
	constexpr uint16_t bcdDevice = 0;
	switch (type)
	{
	case DescriptorType::Device :
		PINB = 0x02;
		PINB = 0x02;
		{
			txBuf[0] = USBPID_DATA0;
			//bDeviceLength
			txBuf[1] = 18;
			//bDescriptorType
			txBuf[2] = static_cast<uint8_t>(DescriptorType::Device);
			//bcdUSB
			txBuf[3] = bcdUSB&0xFF;
			txBuf[4] = bcdUSB>>8;
			//bDeviceClass
			txBuf[5] = 0xFF;
			//bDeviceSubClass
			txBuf[6] = 0xFF;
			//bDeviceProtocol
			txBuf[7] = 0x01;
			//bMaxPacketSize0
			txBuf[8] = 0x08;
			txLen = 9;
			genCRC16();
			//idVendor
			//idProduct
			//bcdDevice
			//iManufacturer
			//iProduct
			//iSerialNumber
			//bNumConfigurations
			
		}
		break;
	case DescriptorType::Configuration :
		break;
	case DescriptorType::Interface :
		break;
	case DescriptorType::Endpoint :
		break;
	case DescriptorType::String :
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
