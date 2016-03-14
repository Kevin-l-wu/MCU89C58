#ifndef WIRELESS_H_
#define WIRELESS_H_

typedef enum _WirelessKey
{
	WIRELESSKEY_A = 0,
	WIRELESSKEY_B,
	WIRELESSKEY_C,
	WIRELESSKEY_D,
	WIRELESSKEY_NONE,
} WIRELESSKEY;


int GetWirelessKey(WIRELESSKEY* key);


#endif