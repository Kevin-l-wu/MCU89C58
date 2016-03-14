#ifndef DIGITRON_H_
#define DIGITRON_H_


typedef enum _Digit {
	DIGIT_0 = 0x3f,
	DIGIT_1 = 0x06,
	DIGIT_2 = 0x5b,
	DIGIT_3 = 0x4f,
	DIGIT_4 = 0x66,
	DIGIT_5 = 0x6d,
	DIGIT_6 = 0x7d,
	DIGIT_7 = 0x07,
	DIGIT_8 = 0x7f,
	DIGIT_9 = 0x6f,
	DIGIT_A = 0x77,
	DIGIT_B = 0x7c,
	DIGIT_C = 0x39,
	DIGIT_D = 0x5e,
	DIGIT_E = 0x79,
	DIGIT_F = 0x71,
	DIGIT_DARK = 0x00,
} DIGIT;

typedef enum _Position {
	POSITION_0 = 0xfe,
	POSITION_1 = 0xfd,
	POSITION_2 = 0xfb,
	POSITION_3 = 0xf7,
	POSITION_4 = 0xef,
	POSITION_5 = 0xdf
} POSITION;

void DigitronInit();

void DigitronDisplay(uchar number, uchar contentNumber);

void DigitronMulripleDisplay(POSITION position, uchar contentNumber);

void RunDigitronTest();


//int DisplayCharValue(POSITION highFourBitPosition, POSITION lowFourBitPosition, uchar destChar);

#endif