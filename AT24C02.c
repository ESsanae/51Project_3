#include <REGX52.H>
#include "I2C.h"

#define AT24C02_Address 0xA0
/**
  * @brief  主机向AT24C02的一个地址中写入一个字节
  * @param  输入 地址 和 数据
  * @retval 无
  //特别注意EEPROM写入时需要Delay(5);，读取时则不需要
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();
	I2C_SendByte(AT24C02_Address);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
	
}

/**
  * @brief  从AT24C02某个地址中读取一个字节的数据
  * @param  要读取的地址
  * @retval 该地址中的数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	
	I2C_Start();
	I2C_SendByte(AT24C02_Address);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_Address|0x01);
	I2C_ReceiveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	
	return Data;
	
}