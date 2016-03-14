#ifndef AT24C02_H_
#define AT24C02_H_

#define AT24C02_MAX_BYTE 2048

void I2cInit();

int At24c02WriteByte(uchar address, uchar date);
int At24c02ReadByte(uchar address, uchar* destChar);

void RunAt24c02Test();

#endif