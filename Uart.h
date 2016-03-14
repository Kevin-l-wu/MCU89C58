#ifndef UART_H_
#define UART_H_

#include "Common.h"

void UartInit();

int PrintChar(uchar destChar);

int PrintString(uchar* destString);

int ReceiveChar(uchar* destChar);

int ReceiverString(uchar* destString, unsigned int length);


#endif