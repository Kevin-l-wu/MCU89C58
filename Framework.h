#ifndef FRAMEWORK1_H_
#define FRAMEWORK1_H_

#define COMMANDLISTLENGTH 16

typedef struct _CommandsList 
{
	char* cmd;
	char* info;
	EVENT event;
	void(*func)();
} COMMANDSLIST;

typedef struct _SoftArray
{
	int capacity;
	int actuaLength;
	COMMANDSLIST* date;
} SoftArray;

MCUSTATUS CreatCommondSoftArray(SoftArray** gCommondSoftArray);
MCUSTATUS CommondInsall(SoftArray** gCommondSoftArray);

#endif
