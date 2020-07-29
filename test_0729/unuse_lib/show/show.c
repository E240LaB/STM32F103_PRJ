#include "show.h"
  /**************************************************************************
?????????
???????http://shop114407458.taobao.com/
**************************************************************************/
/**************************************************************************
?????OLED??
??????
??  ???
**************************************************************************/
void oled_show(void)
{
	if(Run_Flag==0)
	{
		if(Flag_Way==0)	//????
		{
			//=============?1???3???===============//	
			OLED_ShowString(0,0,"X:");
			if(Pitch<0)
				OLED_ShowNumber(15,0,Pitch+360,3,12);
			else
				OLED_ShowNumber(15,0,Pitch,3,12);	
									 
			OLED_ShowString(40,0,"Y:");
			if(Roll<0)
				OLED_ShowNumber(55,0,Roll+360,3,12);
			else
				OLED_ShowNumber(55,0,Roll,3,12);	
							
			OLED_ShowString(80,0,"Z:");
			if(Yaw<0)
				OLED_ShowNumber(95,0,Yaw+360,3,12);
			else
				OLED_ShowNumber(95,0,Yaw,3,12);		
			//=============???Z?????????===============//	
			
			OLED_ShowString(00,10,"GZ");
			if( gyro[2]<0)
				OLED_ShowString(20,10,"-"),OLED_ShowNumber(30,10,-gyro[2],5,12);
			else
				OLED_ShowString(20,10,"+"),OLED_ShowNumber(30,10, gyro[2],5,12);			
							
			OLED_ShowString(70,10,"V");
			OLED_ShowNumber(80,10, RC_Velocity,5,12);	
		}
		else if(Flag_Way==1)//PS2??
		{
			OLED_ShowString(00,0,"LX");
			OLED_ShowNumber(15,0, PS2_LX,3,12);  //PS2???			
			OLED_ShowString(40,0,"LY");
			OLED_ShowNumber(55,0, PS2_LY,3,12);  //PS2???
			OLED_ShowString(80,0,"RX");
			OLED_ShowNumber(95,0, PS2_RX,3,12);
			OLED_ShowString(0,10,"KEY");
			OLED_ShowNumber(25,10,PS2_KEY,2,12);
		}
		else if(Flag_Way==2)//ccd??
		{
			OLED_Show_CCD(); 
			OLED_ShowString(00,10,"Mid");
			OLED_ShowNumber(25,10, CCD_Zhongzhi,3,12);
			OLED_ShowString(65,10,"Light");
			OLED_ShowNumber(105,10, CCD_Yuzhi,3,12);
		}
		else if(Flag_Way==3)//??????
		{
			OLED_ShowString(00,0,"L");
			OLED_ShowNumber(10,0,Sensor_Left,4,12);	
			OLED_ShowString(40,0,"M");
			OLED_ShowNumber(50,0,Sensor_Middle,4,12);
			OLED_ShowString(80,0,"R");
			OLED_ShowNumber(90,0,Sensor_Right,4,12);
			OLED_ShowString(0,10,"Mid");
			OLED_ShowNumber(25,10,Sensor,4,12);		  
		}									
		//=============?3?????A???=======================//	
		if( Target_A<0)
			OLED_ShowString(00,20,"-"),OLED_ShowNumber(15,20,-Target_A,5,12);
		else
			OLED_ShowString(0,20,"+"),OLED_ShowNumber(15,20, Target_A,5,12); 			
		if( Encoder_A<0)
			OLED_ShowString(80,20,"-"),OLED_ShowNumber(95,20,-Encoder_A,4,12);
		else
			OLED_ShowString(80,20,"+"),OLED_ShowNumber(95,20, Encoder_A,4,12);
		
		//=============?4?????B???=======================//	
		if( Target_B<0)
			OLED_ShowString(00,30,"-"),OLED_ShowNumber(15,30,-Target_B,5,12);
		else
			OLED_ShowString(0,30,"+"),OLED_ShowNumber(15,30, Target_B,5,12); 					
		if( Encoder_B<0)
			OLED_ShowString(80,30,"-"),OLED_ShowNumber(95,30,-Encoder_B,4,12);
		else
			OLED_ShowString(80,30,"+"),OLED_ShowNumber(95,30, Encoder_B,4,12);	
		//=============?5?????C???=======================//	
		if( Target_C<0)
			OLED_ShowString(00,40,"-"),OLED_ShowNumber(15,40,-Target_C,5,12);
		else
			OLED_ShowString(0,40,"+"),OLED_ShowNumber(15,40, Target_C,5,12); 				
		if( Encoder_C<0)
			OLED_ShowString(80,40,"-"),OLED_ShowNumber(95,40,-Encoder_C,4,12);
		else
			OLED_ShowString(80,40,"+"),OLED_ShowNumber(95,40, Encoder_C,4,12);
   	}
	else if(Run_Flag==1) //????
	{
		//=============?1???3???===============//	
		OLED_ShowString(0,0,"X:");
		if(Pitch<0)
			OLED_ShowNumber(15,0,Pitch+360,3,12);
		else
			OLED_ShowNumber(15,0,Pitch,3,12);	
				 
		OLED_ShowString(40,0,"Y:");
		if(Roll<0)
			OLED_ShowNumber(55,0,Roll+360,3,12);
		else
			OLED_ShowNumber(55,0,Roll,3,12);	
		
		OLED_ShowString(80,0,"Z:");
		if(Yaw<0)
			OLED_ShowNumber(95,0,Yaw+360,3,12);
		else
			OLED_ShowNumber(95,0,Yaw,3,12);		
	  //=============???Z?????????===============//	
		OLED_ShowString(00,10,"GZ");
		if( gyro[2]<0)
			OLED_ShowString(20,10,"-"),OLED_ShowNumber(30,10,-gyro[2],5,12);
		else
			OLED_ShowString(20,10,"+"),OLED_ShowNumber(30,10, gyro[2],5,12);			
		
		OLED_ShowString(70,10,"P");
		OLED_ShowNumber(80,10, RC_Position,5,12);	
		//=============?3?????A???=======================//	
		if( Target_A<0)
			OLED_ShowString(00,20,"-"),OLED_ShowNumber(15,20,-Target_A,6,12);
		else
			OLED_ShowString(0,20,"+"),OLED_ShowNumber(15,20, Target_A,6,12); 
		
		if( Position_A<0)
			OLED_ShowString(70,20,"-"),OLED_ShowNumber(90,20,-Position_A,6,12);
		else
			OLED_ShowString(70,20,"+"),OLED_ShowNumber(90,20, Position_A,6,12);
 		//=============?4?????B???=======================//	
		if( Target_B<0)
			OLED_ShowString(00,30,"-"),OLED_ShowNumber(15,30,-Target_B,6,12);
		else
			OLED_ShowString(0,30,"+"),OLED_ShowNumber(15,30, Target_B,6,12); 
		
		if( Position_B<0)
			OLED_ShowString(70,30,"-"),OLED_ShowNumber(90,30,-Position_B,6,12);
		else
			OLED_ShowString(70,30,"+"),OLED_ShowNumber(90,30, Position_B,6,12);	
		//=============?5?????C???=======================//	
		if( Target_C<0)
			OLED_ShowString(00,40,"-"),OLED_ShowNumber(15,40,-Target_C,6,12);
		else
			OLED_ShowString(0,40,"+"),OLED_ShowNumber(15,40, Target_C,6,12); 
		
		if( Position_C<0)
			OLED_ShowString(70,40,"-"),OLED_ShowNumber(90,40,-Position_C,6,12);
		else
			OLED_ShowString(70,40,"+"),OLED_ShowNumber(90,40, Position_C,6,12);
	} 
	OLED_ShowString(48,50,".");
	OLED_ShowString(70,50,"V");
	OLED_ShowNumber(35,50,Voltage/100,2,12);
	OLED_ShowNumber(58,50,Voltage%100,2,12);
	
	if(Voltage%100<10)
		OLED_ShowNumber(52,50,0,2,12);
	if(Flag_Stop==0)
		OLED_ShowString(103,50,"O-N");
	if(Flag_Stop==1)
		OLED_ShowString(103,50,"OFF");
	if(Flag_Way==0)
		OLED_ShowString(0,50,"APP");
	else if(Flag_Way==1)
		OLED_ShowString(0,50,"PS2");
	else if(Flag_Way==2)
		OLED_ShowString(0,50,"CCD");
	else if(Flag_Way==3)
		OLED_ShowString(0,50,"ELE");
	OLED_Refresh_Gram();	//?? 

}
/**************************************************************************
??????APP????
??????
??  ???
?    ????????
**************************************************************************/
void APP_Show(void)
{    
	  static u8 flag;
	  int app_2,app_3,app_4;
	  app_4=(Voltage-1110)*2/3;	
	  if(app_4>100)app_4=100;   //?????????
	  app_2=Move_X*0.7;  if(app_2<0)app_2=-app_2;	  //?????????????????
		app_3=Move_Y*0.7;  if(app_3<0)app_3=-app_3;
	   if(Run_Flag==1)app_2=0,app_3=0;
	  flag=!flag;
	 	if(PID_Send==1)//??PID??
	{
		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)RC_Velocity,(int)RC_Position,(int)Position_KP,(int)Position_KI,(int)Position_KD,(int)Velocity_KP,(int)Velocity_KI,0,0);//???APP??	
		PID_Send=0;	
	}	
   else	if(flag==0)// 
   printf("{A%d:%d:%d:%d}$",(u8)app_2,(u8)app_3,app_4,0); //???APP??
	 else
	 printf("{B%d:%d:%d:%d}$",(int)Pitch,(int)Roll,(int)Yaw,app_4);//???APP?? ????
}

void OLED_DrawPoint_Shu(u8 x,u8 y,u8 t)
{ 
	 u8 i=0;
  OLED_DrawPoint(x,y,t);
	OLED_DrawPoint(x,y,t);
	  for(i = 0;i<8; i++)
  {
      OLED_DrawPoint(x,y+i,t);
  }
}

void OLED_Show_CCD(void)  
{ 
	 u8 i,t;
	 for(i = 0;i<128; i++)
  {
		if(ADV[i]<CCD_Yuzhi) t=1; else t=0;
		OLED_DrawPoint_Shu(i,0,t);
  }
}

//?????????
void oled_show_once(void)
{
   OLED_ShowString(0,00,"Turn Right Wheel");
   OLED_ShowString(0,10,"TO Select Mode");
	 OLED_ShowString(0,20,"Current Mode Is");
	if(Flag_Way==0)         OLED_ShowString(50,30,"APP");
	if(Flag_Way==1)         OLED_ShowString(50,30,"PS2");
	if(Flag_Way==2)				  OLED_ShowString(50,30,"CCD");
	if(Flag_Way==3)				  OLED_ShowString(50,30,"ELE");
	
	OLED_ShowString(0,40,"Press User Key");
  OLED_ShowString(0,50,"TO End Selection");
		OLED_Refresh_Gram();	
	}
