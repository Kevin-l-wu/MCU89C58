#ifndef JGD1602_H_
#define JGD1602_H_

#define uchar unsigned char

#define uint unsigned int

void JGD1602Init();
void JGD1602DisplayByte(uchar row, uchar colum, uchar destChar);
void JGD1602DisplayText(uchar row, uchar colum, uchar destString[]);

void RunJDG1602Test();

#endif
