#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;
/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void I2C_Start()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2C_SDA = 0;
	I2C_SCL = 0;
	
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void I2C_Stop()
{
	I2C_SDA = 0;
	I2C_SCL = 1;
	I2C_SDA = 1;
}
/**
  * @brief  I2C发送一个字节
  * @param  无
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);
		I2C_SCL = 1;
		I2C_SCL = 0;
	
	}
}
/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval 接受到的数据
  */
unsigned char I2C_ReceiveByte()
{	
	unsigned char i;
	unsigned char Byte = 0x00;
	I2C_SDA = 1;
	for(i=0;i<8;i++)
	{
		I2C_SCL = 1;
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL = 0;
	}
	
	
	
	return Byte;
}
/**
  * @brief  主机发送应答
  * @param  要发送的应答 0是应答 1是非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)//主机发送应答
{
		I2C_SDA = AckBit;
		I2C_SCL = 1;	
		I2C_SCL = 0;	
}
/**
  * @brief  主机接收应答
  * @param  无
  * @retval 接受到的应答 0是应答 1是非应答
  */
unsigned char I2C_ReceiveAck()//主机接收应答
{ 
	unsigned char AckBit;
	I2C_SDA = 1;
	I2C_SCL = 1;
	AckBit = I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}