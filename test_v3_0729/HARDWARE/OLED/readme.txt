	函式名稱						用途

OLED_SHOW_Info(void)					顯示資訊(Encoder PWM)

OLED_SHOW_String(u8 x,u8 y, const u8 *p)		顯示字串

OLED_SHOW_Number(u8 x,u8 y,u32 num,u8 len,u8 size)	顯示數字

OLED_SHOW_Char(u8 x,u8 y,u8 chr,u8 size,u8 mode)	顯示字元

OLED_SHOW_DRAWPOINT(u8 x,u8 y,u8 t)

OLED_SHOW_POW(u8 m,u8 n)

OLED_SHOW_WR_Byte(u8 dat,u8 cmd)			

OLED_SHOW_INIT(void)					OLED初始化

OLED_SHOW_Refresh(void)					OLED更新

OLED_Off(void)						OLED關閉

OLED_On(void)						OLED開啟

OLED_Clean(void)					清除OLED

