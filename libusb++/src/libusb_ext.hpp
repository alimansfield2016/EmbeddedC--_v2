#pragma once

/*
AVR C++ Standard Library
Written by Alex Mansfield
Copyright 2020

AVR USB Extended Header

The <> header includes:

*/


extern "C" {
	#include "usbdrv.h"

	extern volatile uint8_t usbInputBufOffset;
	extern volatile uint8_t usbRxBuf[11];
	extern volatile uint8_t usbDeviceAddr;
	extern volatile uint8_t usbCurrentTok;
	extern volatile uint8_t usbRxLen;
	// extern uint8_t usbTxLen;
	// extern uint8_t usbTxBuf[11];
	// extern uint8_t usbRxToken;
	extern volatile uint8_t usbNewDeviceAddr;

	// extern uint8_t* usbTxLens[16];
	extern volatile uint8_t* usbTxLenBufs[16];

	void handleTransaction();
}