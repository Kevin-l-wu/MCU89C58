#include <string.h>
#include <stdio.h>

#include "Message.h"

static MESSAGE gQueueArray[QUEUE_ARRAY_CAPACITY];

static int gQueueArrayHead = 0;
static int gQueueArrayTail = 0;
static int gQueueArrayLength = 0;

int MessageInit()
{	
	gQueueArrayHead = 0;
	gQueueArrayTail = 0;
	gQueueArrayLength = 0;
	
	memset(gQueueArray, 0, sizeof(gQueueArray));
	
	return 0;
}

int SendMessage(MESSAGE* message)
{
	/*Make sure the length of the queue do not more then 8*/
	if(gQueueArrayLength < QUEUE_ARRAY_CAPACITY)
	{
		gQueueArray[gQueueArrayTail].type = (*message).type;
		gQueueArray[gQueueArrayTail].event = (*message).event;
		
		if(gQueueArrayTail < (QUEUE_ARRAY_CAPACITY - 1))
		{
			gQueueArrayTail++;
		}
		else
		{
			gQueueArrayTail = 0;
		}
		
		gQueueArrayLength++;
	}
	else
	{
		printf("The array is full, do not insert\n");
	}
	
	return 0;
}

int GetMessage(MESSAGE* message)
{
	if(gQueueArrayLength > 0)
	{
		(*message).type = gQueueArray[gQueueArrayHead].type;
		(*message).event = gQueueArray[gQueueArrayHead].event;
	
		if(gQueueArrayHead < (QUEUE_ARRAY_CAPACITY - 1))
		{
			gQueueArrayHead++;
		}
		else
		{
			gQueueArrayHead = 0;
		}
		
		gQueueArrayLength--;
	}else
	{
		printf("The queue array is empty, do not get\n");
	}

	return 0;
}