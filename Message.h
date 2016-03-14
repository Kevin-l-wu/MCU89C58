#ifndef MESSAGE_H_
#define MESSAGE_H_

#define QUEUE_ARRAY_CAPACITY 8

typedef enum _Event
{
	MessageEventPrintNone,
	MessageEventPrintVersion,
	MessageEventPrintHelp,
	MessageEventPrintSN,
	MessageEventLedTest,
	MessageEventFengMingTest,
	MessageEventDigitronTest,
	MessageEventDs18b20Test,
	MessageEventADConvertTest,
	MessageEventDAConvertTest,
	MessageEventAt24c02Test,
	MessageEventJDG1602Test
} EVENT;

typedef enum _Type
{
	MessageTypeNone,
	MessageTypePrint,
	MessageTypeWrite
} TYPE;

typedef struct _Message
{
	TYPE type;
	EVENT event;
} MESSAGE;


int MessageInit();

int SendMessage(MESSAGE* message);

int GetMessage(MESSAGE* message);

#endif