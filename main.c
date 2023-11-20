#include <REGX52.H>
#include "LCD1602.H"
#include "DS18B20.H"
#include "Delay.H"
#include "T0Key.H"
#include "AT24C02.H"

//sbit Buzzer = P2^5;


float T;
char TLOW,THIGH;
unsigned char KeyNum;
unsigned char TCSelect;

void main()
{
	THIGH=AT24C02_ReadByte(0);
	TLOW=AT24C02_ReadByte(1);
	Timer0Init();
	LCD_Init();
	DS18B20_ConvertT();//DS18B20温度转换需要时间，如果不延迟则读取的上一个温度
	Delay(800);
	LCD_ShowString(1,9,"<");
	LCD_ShowString(1,12,">");
	LCD_ShowString(1,10,"00");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THIGH,3);
	LCD_ShowSignedNum(2,12,TLOW,3);		
	while(1)
	{
		KeyNum = Key();
		/*温度读取及显示部分*/
		T = DS18B20_ReadT();
		DS18B20_ConvertT();
		if(T<0)
		{
			LCD_ShowChar(1,1,'-');
		}
		else
		{
			LCD_ShowChar(1,1,'+');
		}
		LCD_ShowNum(1,2,T,3);
		LCD_ShowChar(1,5,'.');
		LCD_ShowNum(1,6,(unsigned long)(T*100)%100,2);
		/*阈值操作及显示部分*/
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				TCSelect++;
			}
			if(TCSelect>=3){TCSelect=0;}
			if(TCSelect==1)
			{
				if(KeyNum==2){THIGH++;if(THIGH>=125){THIGH=125;}}
				if(KeyNum==3){THIGH--;if(THIGH<=TLOW){THIGH++;}if(THIGH<=-55){THIGH=-55;}}
			}
			if(TCSelect==2)
			{
				if(KeyNum==2){TLOW++;if(TLOW>=THIGH){TLOW--;}if(TLOW>=125){TLOW=125;}}
				if(KeyNum==3){TLOW--;if(TLOW<=-55){TLOW=-55;}}
		
		    }
			if(TCSelect==0){LCD_ShowString(1,10,"00");}
			if(TCSelect==1){LCD_ShowString(1,10,"TH");}
			if(TCSelect==2){LCD_ShowString(1,10,"TL");}
			LCD_ShowSignedNum(2,12,TLOW,3);
			LCD_ShowSignedNum(2,4,THIGH,3);
			AT24C02_WriteByte(0,THIGH);
			Delay(5);
			AT24C02_WriteByte(1,TLOW);
			Delay(5);
			
	    }
		/*阈值判断部分*/
		if(T>THIGH)
		{
			LCD_ShowString(1,13,"OVH!");
		}
		else if(T<TLOW)
		{
			LCD_ShowString(1,13,"OVC!");
		}
		else
		{
			LCD_ShowString(1,13,"GOOD");
		}
		
	}
	
}

void Timer0_Rountine() interrupt 1
{  
	static unsigned int Count0;//,Count1;
	TL0 = 0x66;		 
	TH0 = 0xFC;
	Count0++;
	if(Count0>=20)
	{
		Count0=0;
		Key_Loop();
	}
//	if(T>THIGH||T<TLOW)
//	{
//		Count1++;
//		if(Count1>=20)
//		{
//			Count1=0;
//			Buzzer=~Buzzer;
//		}
//	}

}