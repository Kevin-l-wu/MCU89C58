#ifndef COMMON_H_
#define COMMON_H_

#define uint unsigned int
#define uchar unsigned char

#define DEBUGON 0
#define MAX_NUMBER_DIGITRON 6

extern char isTimer0Continue;
extern int gTimer0DelayMs;

void Delay(uint z);
void Timer0DelayMs(uint ms);
int IsTimer0Timeout();

void CleanString(char* destString);

void UcharNumberToAscii(uchar destNumber, uchar* asciiCode);
//void UintNumberToAscii(uint destNumber, uchar* asciiCode);
#endif