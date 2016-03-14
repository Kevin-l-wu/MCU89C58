#ifndef MESSAGE_H_
#define MESSAGE_H_

#define DEBUG

#define QUEUE_ARRAY_CAPACITY 8

typedef enum _Event
{
	MessageEventDigitronSingle,
	MessageEventDigitronMultiple
} EVENT;

typedef enum _Type
{
	MessageEventPrint = 0,
	MessageEventWrite
} TYPE;

typedef struct _Message
{
	TYPE type;
	EVENT event;
	int number;
} MESSAGE;


int MessageInit();

int SendMessage(MESSAGE* message);

int GetMessage(MESSAGE* message);

#endif