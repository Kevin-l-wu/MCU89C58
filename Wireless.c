#include <reg52.h>

#include "Wireless.h"

sbit keyD = P3^4;
sbit keyC = P3^5;
sbit keyB = P3^6;
sbit keyA = P3^7;
sbit linghtD = P1^3;
sbit linghtC = P1^2;
sbit linghtB = P1^1;
sbit linghtA = P1^0;


int GetWirelessKey(WIRELESSKEY* key)
{
	if(keyD == 1)
	{
		linghtD = 0;
		*key = WIRELESSKEY_D;
	}
	else
	{
		linghtD = 1;
	}
	
	if(keyC == 1)
	{
		linghtC = 0;
		*key = WIRELESSKEY_C;
	}
	else
	{
		linghtC = 1;
	}
	
	if(keyB == 1)
	{
		linghtB = 0;
		*key = WIRELESSKEY_B;
	}
	else
	{
		linghtB = 1;
	}

	
	if(keyA == 1)
	{
		linghtA = 0;
		*key = WIRELESSKEY_A;
	}
	else
	{
		linghtA = 1;
	}

	P0 = 0xff;


	return 0;
}