#include <REGX52.H>
#include "OneWire.H"


//由于单总线时序(绝对时间)在进行时需关闭中断 会对整体造成非常大的影响


#define DS18B20_Skip_ROM 0xCC
#define DS18B20_Convert_T 0x44
#define DS18B20_Read_SCRATCHPAD 0xBE
/**
  * @brief  主机发送初始化指令并且向DS18B20发送温度变换的指令
  * @param  无
  * @retval 无
  */
void DS18B20_ConvertT()
{
	EA= 0;
	OneWire_Init();
	OneWire_SendByte(DS18B20_Skip_ROM);
	OneWire_SendByte(DS18B20_Convert_T);
	EA = 1;
}

/**
  * @brief  接收温度数值
  * @param  无
  * @retval  T  float类型  补码形式
  */
float DS18B20_ReadT()
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	EA = 0;//防止所有的中断程序影响OneWire的时序
	OneWire_Init();
	OneWire_SendByte(DS18B20_Skip_ROM);
	OneWire_SendByte(DS18B20_Read_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();
	Temp = (TMSB<<8)|TLSB;
	T = Temp/16.0;
	EA = 1;

	return T;
}