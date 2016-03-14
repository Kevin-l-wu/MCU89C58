#ifndef ERROR_H_
#define ERROR_H_

typedef enum _McuStatus
{
	McuStatusSuccess = 0,
	McuStatusInvalidParameter = -1,
	McuStatusMemeryShortage = -2
} MCUSTATUS;


MCUSTATUS ErrorMessagePrint(MCUSTATUS mcuStatus);
MCUSTATUS ErrorCheck(MCUSTATUS mcuStatus);

#endif

