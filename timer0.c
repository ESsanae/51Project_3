#include <REGX52.H>
 /**
  * @brief  定时器0的初始化，1毫秒 11.0562MHZ
  * @param  无
  * @retval 无
  */


void Timer0Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 1;
    ET0=1;
	EA=1;
	PT0=0;

}

//void Timer0_Rountine() interrupt 1    //中断函数模板
//{
//	static unsigned int Count0;
//	TL0 = 0x66;		 
//	TH0 = 0xFC;
//	Count0++;
//	if(Count0>=1000)
//	{
//		Count0=0;
//	}
//}