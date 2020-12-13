/*
jinwenhao

*/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void Delay(uint Temp);  //子函数声明

void main(void) 
{
  uchar b=0x01,c=0x80;
  EnableInterrupts; /* enable interrupts */
  SOPT_COPE=0;   //关闭看门狗复位功能，避免程序复位
  PTBDD=0xff;   //定义PTB八个引脚为输出
  PTBD=0xff;    //初始化PTB八个引脚输出高电平
  PTCDD=0xfc;  //定义PTC0和PTC0引脚为输入
  PTCPE=0x03;  //定义PTC0和PTC0引脚为上拉电阻
  for(;;)
  {
    __RESET_WATCHDOG(); /* feeds the dog */
  if(!PTCD_PTCD0&&PTCD_PTCD1)  //开关1按下
  {
  	
      PTBD=0x00;   //8个LED一起亮
  	Delay(1000);
  	
      PTBD=0xff;   //8个LED一起灭
  	Delay(1000);
  }
 
  if(PTCD_PTCD0&&!PTCD_PTCD1)  开关2按下
  {
  	
      PTBD=0xf0;    //前4个LED一起亮，后4个LED一起灭
  	Delay(1000);
  	
      PTBD=0x0f;    //前4个LED一起灭，后4个LED一起亮
  	Delay(1000);	
  }
  if(!PTCD_PTCD0&&!PTCD_PTCD1)  //开关1、2都按下，右流水灯
  {
   
    PTBD=~b;
    Delay(1000);
    
    b=b<<1;
    if(b==0x00)
  
  	b=0x01;
  }
  
  if(PTCD_PTCD0&&PTCD_PTCD1)  //开关1、2都不按下，左流水灯
  
  {
    PTBD=~c;
    Delay(1000);
    c=c>>1;
    if(c==0x00)
  	c=0x80;
  }
  } 
}

void Delay(uint Temp)  //延时函数，单位是ms
{
	uchar a,b;
	for(;Temp>0;Temp--)
	{
		for(b=30;b>0;b--)
		{
			for(a=10;a>0;a--);
		}
	}
}
