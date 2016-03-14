#include<reg52.h>
#include<intrins.h>

#include "Common.h"
#include "StepMotor.h"

uchar code CCW[8] = {0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01, 0x09};   //��ʱ����ת�����
uchar code CW[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08};    //��ʱ����ת�����

sbit FMQ = P2^3;  //  ������


void Beep(void)
{
	uchar times = 0;
	for(times = 0; times < 100; times++)
	{
		Delay(1);
		FMQ = !FMQ;   //��������
	}
	FMQ = 1;    //�رշ�����
}

void MotorCounterClockwise(void)
{
	uchar i = 0, j = 0;
	
	for(j = 0; j < 8; j++)                 //�����תһ�ܣ�����������������һ�ܣ�������Ĵ�����ת��һ��
	{
		for(i = 0; i < 8; i++)  //��ת45��
		{
			P0 = (CCW[i] & 0x0f) << 2;
			Delay(1);   //����ת��
		}
	}
}


void MotorClockwise(void)
{
	uchar i, j;

	for(j = 0; j < 8; j++)
	{
		for(i = 0; i < 8; i++)  //��ת45��
		{
			P0 = (CW[i] & 0x0f) << 2;
			Delay(1);   //����ת��
		}
	}
}






