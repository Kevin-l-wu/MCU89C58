#include "Uart.h"
#include "Error.h"


MCUSTATUS ErrorMessagePrint(MCUSTATUS mcuStatus)
{
	MCUSTATUS mcuStatusRet = McuStatusSuccess;
	
	switch(mcuStatus)
	{
		case McuStatusSuccess:
			PrintString("Mcu Status: Success\n");
			break;
		case McuStatusInvalidParameter:
			PrintString("Mcu Status: Invalid Parameter\n");
			break;
		case McuStatusMemeryShortage:
			PrintString("Mcu Status: Memery Shortage\n");
			break;
		default:
			PrintString("Mcu Status: Invalid Status\n");
			break;
	}
	
	mcuStatusRet = mcuStatus;
	
	return mcuStatusRet;
}

MCUSTATUS ErrorCheck(MCUSTATUS mcuStatus)
{
	MCUSTATUS mcuStatusRet = McuStatusSuccess;
	
	if( mcuStatus != McuStatusSuccess )
	{
		ErrorMessagePrint(mcuStatus);
		PrintString("Hang...");
		while(1);
	}
	
	mcuStatusRet = mcuStatus;
	
	return mcuStatusRet;
}
