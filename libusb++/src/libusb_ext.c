#include <stdint.h>


uint8_t usbInputBufOffset;
uint8_t usbRxBuf[11];
uint8_t usbDeviceAddr;
uint8_t usbCurrentTok;
uint8_t usbRxLen;
uint8_t usbTxLen;
uint8_t usbTxBuf[11];
uint8_t usbRxToken;
uint8_t usbNewDeviceAddr;

uint8_t usbEndptNo;
uint8_t usbTransactionEnd;