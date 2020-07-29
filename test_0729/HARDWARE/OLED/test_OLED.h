#ifndef __OLED_H
#define __OLED_H
#include "system_init.h"

//---------------OLED定義---------------//
#define OLED_RST_Clr() PCout(14)=0   //RST
#define OLED_RST_Set() PCout(14)=1   //RST

#define OLED_RS_Clr() PCout(13)=0    //DC
#define OLED_RS_Set() PCout(13)=1    //DC

#define OLED_SCLK_Clr()  PCout(0)=0  //SCL
#define OLED_SCLK_Set()  PCout(0)=1   //SCL

#define OLED_SDIN_Clr()  PCout(15)=0   //SDA
#define OLED_SDIN_Set()  PCout(15)=1   //SDA

#define OLED_CMD  0	//寫命令
#define OLED_DATA 1	//寫數據

extern void OLED_SHOW_Info(void);
extern void OLED_SHOW_String(u8 x,u8 y, const u8 *p);
extern void OLED_SHOW_Char(u8 x,u8 y,u8 chr,u8 size,u8 mode);

extern void OLED_SHOW_Number(u8 x,u8 y,u32 num,u8 len,u8 size);
extern void OLED_SHOW_DRAWPOINT(u8 x,u8 y,u8 t);
extern u32 OLED_SHOW_POW(u8 m,u8 n);

extern void OLED_SHOW_WR_Byte(u8 dat,u8 cmd);			
extern void OLED_SHOW_INIT(void);			
extern void OLED_SHOW_Refresh(void);	

extern void OLED_Off(void);
extern void OLED_On(void);
extern void OLED_Clean(void);

#endif  
