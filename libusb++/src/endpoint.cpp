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

Endpoint::Endpoint() : txLen(txLenBuf[0]), txBuf(&txLenBuf[1])
{
	txLen = 0;
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
}
