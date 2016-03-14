#include <reg52.h>

#include "Keyboard.h"
#include "Common.h"

uchar code gMatrixKeyValue[] = 
{
	0xee, 0xde, 0xbe, 0x7e,
	0xed, 0xdd, 0xbd, 0x7d,
	0xeb, 0xdb, 0xbb, 0x7b,
	0xe7, 0xd7, 0xb7, 0x77
};


int GetMatrixKey(MATRIX_KEY* matrixKey)
{
	uchar i = 0;

	for(i = 0; i < (sizeof(gMatrixKeyValue)/sizeof(gMatrixKeyValue[0])); i++)
	{
		P3 = gMatrixKeyValue[i] | 0xf0;	
			
		if((P3 & 0xf0) == (gMatrixKeyValue[i] & 0xf0))
		{
			Delay(5);
			if((P3 & 0xf0) == (gMatrixKeyValue[i] & 0xf0))
			{
				*matrixKey = i+1;
				break;
			}
		}
	}

	return 0;
}

int GetSingleKey(SINGLE_KEY* singleKey)
{
	if((P3 & SINGLE_KEY1) == 0)
	{
		Delay(10);
		if((P3 & SINGLE_KEY1) == 0)
		{
			 *singleKey = SINGLE_KEY1;
		}
	
	}else if((P3 & SINGLE_KEY2) == 0)
	{
		Delay(10);
		if((P3 & SINGLE_KEY2) == 0)
		{
			 *singleKey = SINGLE_KEY2;
		}
	}else if((P3 & SINGLE_KEY3) == 0)
	{
		Delay(10);
		if((P3 & SINGLE_KEY3) == 0)
		{
			 *singleKey = SINGLE_KEY3;
		}
	}else if((P3 & SINGLE_KEY4) == 0)
	{
		Delay(10);
		if((P3 & SINGLE_KEY4) == 0)
		{
			 *singleKey = SINGLE_KEY4;
		}
	}else
	{
		*singleKey = SINGLE_NONE;	
	}


	return 0;
}
