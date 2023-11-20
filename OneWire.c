#include <REGX52.H>
#include <Intrins.h>

sbit OneWire_DQ = P3^7;
/**
  * @brief  初始化
  * @param  无
  * @retval （方便调试）可无
  */
unsigned char OneWire_Init()
{
	unsigned char i,j;
	unsigned char AckBit;
	OneWire_DQ = 1;
	OneWire_DQ = 0;
	i = 227;while (--i);
	OneWire_DQ = 1;
    i = 27;while (--i);
	AckBit = OneWire_DQ;
	i = 6;j = 107;do{while (--j);} while (--i);//Delay500us
	return AckBit;
}
/**
  * @brief  主机发送一个Bit
  * @param  无
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ = 0;
	i = 4;while (--i);
	OneWire_DQ = Bit;
	i = 25;while (--i);
	OneWire_DQ = 1;
}
/**
  * @brief  主机接收一个bit
  * @param  无
  * @retval 接收到的bit
  */
unsigned char OneWire_ReceiveBit()
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ = 0;
	_nop_();_nop_();_nop_();
	OneWire_DQ = 1;
	i = 3;while (--i);
	Bit = OneWire_DQ;
	i = 24;while (--i);
	return Bit;
}
/**
  * @brief  主机发送一个字节
  * @param  要发送的字节（一般是命令）
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
	//unsigned char Bit;
	unsigned char i;
	for(i=0;i<8;i++)
	{
		//Bit = Byte&(0x01<<i);
		OneWire_SendBit(Byte&(0x01<<i));
	}
	
}
/**
  * @brief  主机接收一个字节
  * @param  无
  * @retval 接收到的字节
  */
unsigned char OneWire_ReceiveByte()
{
	unsigned char Byte = 0x00;
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<i);}
	}
	return Byte;
}
