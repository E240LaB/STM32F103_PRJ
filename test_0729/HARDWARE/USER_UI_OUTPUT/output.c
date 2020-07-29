#include "output.h"
//output function

void Motion_Transfer(int ux, int uy, int ut) {
	
	int _Vx,_Vy,_Vw;
	
	_Vx = ux * 0.005;
	_Vy = uy * 0.005;
	_Vw = ut * 0.005 * 1.414;
	
	motor_A =  200 * (_Vy + _Vx - _Vw*0.19);
	motor_B =  200 * (_Vy - _Vx + _Vw*0.19);
	motor_C =  200 * (_Vy + _Vx + _Vw*0.19);
	motor_D =  200 * (_Vy - _Vx - _Vw*0.19);
	
	Motor_PWM_PWM_A(motor_A);
	Motor_PWM_PWM_B(motor_B);
	Motor_PWM_PWM_C(motor_C);
	Motor_PWM_PWM_D(motor_D);
	
}
void Robot_power_out(int uA, int uB, int uC, int uD) {
	Motor_PWM_PWM_A(uA);
	Motor_PWM_PWM_B(uB);
	Motor_PWM_PWM_C(uC);
	Motor_PWM_PWM_D(uD);
}


void Robot_Dir(int mode, int power)
{
	switch(mode)
	{
		case 1:
			Motion_Transfer(0,power,0);
			delay_ms(500);
			Robot_power_out(0,0,0,0);
			mode = 22;
		break;
		case 2:
			Motion_Transfer(0,-power,0);
			delay_ms(500);
			Robot_power_out(0,0,0,0);
			mode = 22;
		break;
		case 3:
			Motion_Transfer(power*0.707,power,0);
			delay_ms(500);
			Robot_power_out(0,0,0,0);
			mode = 22;
		break;
		case 4:
			Motion_Transfer(-power*0.707,-power,0);
			delay_ms(500);
			Robot_power_out(0,0,0,0);
			mode = 22;
		break;
	}
}
//input function
