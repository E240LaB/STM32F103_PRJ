#include "test_OLED.h"
#include "stdlib.h"
#include "oledfont.h"
#include "delay.h"

u8 OLED_GRAM2[128][8];	

void OLED_SHOW_INIT(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PB端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能AFIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;     //2M
	GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIO 

	
	PWR_BackupAccessCmd(ENABLE);//允许修改RTC 和后备寄存器
	RCC_LSEConfig(RCC_LSE_OFF);//关闭外部低速外部时钟信号功能 后，PC13 PC14 PC15 才可以当普通IO用。
	BKP_TamperPinCmd(DISABLE);//关闭入侵检测功能，也就是 PC13，也可以当普通IO 使用
	PWR_BackupAccessCmd(DISABLE);//禁止修改后备寄存器

	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
					  
	OLED_SHOW_WR_Byte(0xAE,OLED_CMD); //关闭显示
	OLED_SHOW_WR_Byte(0xD5,OLED_CMD); //设置时钟分频因子,震荡频率
	OLED_SHOW_WR_Byte(80,OLED_CMD);   //[3:0],分频因子;[7:4],震荡频率
	OLED_SHOW_WR_Byte(0xA8,OLED_CMD); //设置驱动路数
	OLED_SHOW_WR_Byte(0X3F,OLED_CMD); //默认0X3F(1/64) 
	OLED_SHOW_WR_Byte(0xD3,OLED_CMD); //设置显示偏移
	OLED_SHOW_WR_Byte(0X00,OLED_CMD); //默认为0

	OLED_SHOW_WR_Byte(0x40,OLED_CMD); //设置显示开始行 [5:0],行数.
													    
	OLED_SHOW_WR_Byte(0x8D,OLED_CMD); //电荷泵设置
	OLED_SHOW_WR_Byte(0x14,OLED_CMD); //bit2，开启/关闭
	OLED_SHOW_WR_Byte(0x20,OLED_CMD); //设置内存地址模式
	OLED_SHOW_WR_Byte(0x02,OLED_CMD); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_SHOW_WR_Byte(0xA1,OLED_CMD); //段重定义设置,bit0:0,0->0;1,0->127;
	OLED_SHOW_WR_Byte(0xC0,OLED_CMD); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	OLED_SHOW_WR_Byte(0xDA,OLED_CMD); //设置COM硬件引脚配置
	OLED_SHOW_WR_Byte(0x12,OLED_CMD); //[5:4]配置
		 
	OLED_SHOW_WR_Byte(0x81,OLED_CMD); //对比度设置
	OLED_SHOW_WR_Byte(0xEF,OLED_CMD); //1~255;默认0X7F (亮度设置,越大越亮)
	OLED_SHOW_WR_Byte(0xD9,OLED_CMD); //设置预充电周期
	OLED_SHOW_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_SHOW_WR_Byte(0xDB,OLED_CMD); //设置VCOMH 电压倍率
	OLED_SHOW_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_SHOW_WR_Byte(0xA4,OLED_CMD); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_SHOW_WR_Byte(0xA6,OLED_CMD); //设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	OLED_SHOW_WR_Byte(0xAF,OLED_CMD); //开启显示	 
	OLED_Clean();
}  

void OLED_SHOW_Off(void)
{
	OLED_SHOW_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_SHOW_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_SHOW_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

void OLED_SHOW_On(void)
{
	OLED_SHOW_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_SHOW_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_SHOW_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

void OLED_Clean(void)
{
	u8 i,n;  
	for(i=0;i<8;i++)
		for(n=0;n<128;n++)
			OLED_GRAM2[n][i]=0X00;  
	OLED_SHOW_Refresh();//更新显示
}

void OLED_SHOW_Refresh(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_SHOW_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_SHOW_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_SHOW_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			OLED_SHOW_WR_Byte(OLED_GRAM2[n][i],OLED_DATA); 
	}   
}

void OLED_SHOW_WR_Byte(u8 dat,u8 cmd)
{
	u8 i;			  
	if(cmd)
		OLED_RS_Set();
	else 
		OLED_RS_Clr();		  
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_RS_Set();   	
}

void OLED_SHOW_String(u8 x,u8 y, const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clean();}
        OLED_SHOW_Char(x,y,*p,12,1);	 
        x+=8;
        p++;
    }  
}	   

void OLED_SHOW_Number(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_SHOW_POW(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_SHOW_Char(x+(size/2)*t,y,' ',size,1);
				continue;
			}
			else
				enshow=1; 		 	 
		}
	 	OLED_SHOW_Char(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 

u32 OLED_SHOW_POW(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)
		result*=m;    
	return result;
}

void OLED_SHOW_Char(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';//得到偏移后的值				   
    for(t=0;t<size;t++)
    {   
		if(size==12)
			temp=oled_asc2_1206_2[chr][t];  //调用1206字体
		else
			temp=oled_asc2_1608_2[chr][t];		 //调用1608字体 	                          
        for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
				OLED_SHOW_DRAWPOINT(x,y,mode);
			else 
				OLED_SHOW_DRAWPOINT(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}

void OLED_SHOW_DRAWPOINT(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)
		return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)
		OLED_GRAM2[x][pos]|=temp;
	else 
		OLED_GRAM2[x][pos]&=~temp;	    
}

void OLED_SHOW_Info()
{
	/*******************MOTOR A INFORMATION******************/
	OLED_SHOW_String(0,0,"enA");
	if (othetaA > 0)
		OLED_SHOW_String(25,0,"+");
	else if (othetaA == 0)
		OLED_SHOW_String(25,0," ");
	else
		othetaA = (abs(othetaA) - othetaA)/2,OLED_SHOW_String(25,0,"-"),OLED_SHOW_Number(35,0,othetaA,5,12);
	
	OLED_SHOW_Number(35,0,othetaA,5,12);
	OLED_SHOW_String(70,0,"pwA");
	if(motor_A > 0)
		OLED_SHOW_String(95,0,"+");
	else if(motor_A == 0)
		OLED_SHOW_String(95,0," ");
	else
		motor_A = (abs(motor_A) - motor_A)/2,OLED_SHOW_String(95,0,"-"),OLED_SHOW_Number(100,0,motor_A,4,12);
	
	OLED_SHOW_Number(100,0,motor_A,4,12);
	
	/*******************MOTOR B INFORMATION******************/
	OLED_SHOW_String(0,10,"enB:");
	if (othetaB > 0)
		OLED_SHOW_String(25,10,"+");
	else if (othetaB == 0)
		OLED_SHOW_String(25,10," ");
	else
		othetaB = (abs(othetaB) - othetaB)/2,OLED_SHOW_String(25,10,"-"),OLED_SHOW_Number(35,10,othetaB,5,12);
	
	OLED_SHOW_Number(35,10,othetaB,5,12);
	
	
	OLED_SHOW_String(70,10,"pwB:");
	if(motor_B > 0)
		OLED_SHOW_String(95,10,"+");
	else if(motor_B == 0)
		OLED_SHOW_String(95,10," ");
	else
		motor_B = (abs(motor_B) - motor_B)/2,OLED_SHOW_String(95,10,"-"),OLED_SHOW_Number(100,10,motor_B,4,12);
	OLED_SHOW_Number(100,10,motor_B,4,12);
	
	/*******************MOTOR C INFORMATION******************/
	OLED_SHOW_String(0,20,"enC:");
	if (othetaC > 0)
		OLED_SHOW_String(25,20,"+");
	else if (othetaC == 0)
		OLED_SHOW_String(25,20," ");
	else
		othetaC = (abs(othetaC) - othetaC)/2,OLED_SHOW_String(25,20,"-"),OLED_SHOW_Number(35,20,othetaC,5,12);
	
	OLED_SHOW_Number(35,20,othetaC,5,12);
	OLED_SHOW_String(70,20,"pwC:");
	if(motor_C > 0)
		OLED_SHOW_String(95,20,"+");
	else if(motor_C == 0)
		OLED_SHOW_String(95,20," ");
	else
		motor_C = (abs(motor_C) - motor_C)/2,OLED_SHOW_String(95,20,"-"),OLED_SHOW_Number(100,20,motor_C,4,12);
	OLED_SHOW_Number(100,20,motor_C,4,12);
	
	/*******************MOTOR D INFORMATION******************/
	OLED_SHOW_String(0,30,"enD:");
	if (othetaD > 0)
		OLED_SHOW_String(25,30,"+");
	else if (othetaD == 0)
		OLED_SHOW_String(25,30," ");
	else
		othetaD = (abs(othetaD) - othetaD)/2,OLED_SHOW_String(25,30,"-"),OLED_SHOW_Number(35,30,othetaD,5,12);
	
	OLED_SHOW_Number(35,30,othetaD,5,12);
	OLED_SHOW_String(70,30,"pwD:");
	if(motor_D > 0)
		OLED_SHOW_String(95,30,"+");
	else if(motor_D == 0)
		OLED_SHOW_String(95,30," ");
	else
		motor_D = (abs(motor_D) - motor_D)/2,OLED_SHOW_String(95,30,"-"),OLED_SHOW_Number(100,30,motor_D,4,12);
	OLED_SHOW_Number(100,30,motor_D,4,12);
		OLED_SHOW_Refresh();

}
