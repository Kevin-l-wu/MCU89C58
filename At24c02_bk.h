#ifndef AT24C02_H_
#define AT24C02_H_


int At24c02ReadByte(uchar address, uchar* destChar);

int At24c02WriteByte(uchar address, uchar destChar);

int At24c02Read(uchar address, uchar length, uchar* destChar);

int At24c02Write(uchar address, uchar* destChar, uchar length);


#endif