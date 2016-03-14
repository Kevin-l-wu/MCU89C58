#include<reg52.h>
#include<intrins.h>

#include "Common.h"
#include "StepMotor.h"

uchar code CCW[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};   //逆时钟旋转相序表
uchar code CW[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08};    //正时钟旋转相序表

sbit FMQ = P2^3;  //  蜂鸣器


void Beep(void)
{
	uchar times = 0;
	for(times = 0; times < 100; times++)
	{
		Delay(1);
		FMQ = !FMQ;   //产生脉冲
	}
	FMQ = 1;    //关闭蜂鸣器
}

void MotorCounterClockwise(void)
{
	uchar i = 0, j = 0;
	
	for(j = 0; j < 8; j++)                 //电机旋转一周，不是外面所看到的一周，是里面的传动轮转了一周
	{
		for(i = 0; i < 8; i++)  //旋转45度
		{
			P0 = (CCW[i] & 0x0f) << 2;
			Delay(1);   //调节转速
		}
	}
}


void MotorClockwise(void)
{
	uchar i, j;

	for(j = 0; j < 8; j++)
	{
		for(i = 0; i < 8; i++)  //旋转45度
		{
			P0 = (CW[i] & 0x0f) << 2;
			Delay(1);   //调节转速
		}
	}
}






