#include "output.h"
//output function

void Motion_Transfer(float ux, float uy, float ut) {
	
	motor_A =  ux + uy -ut;
	motor_B = -ux + uy -ut;
	motor_C = -ux + uy +ut;
	motor_D =  ux + uy +ut;
	
}
void Robot_power_out(float uA, float uB, float uC, float uD) {
	Motor_PWM_PWM_A(uA);
	Motor_PWM_PWM_B(uB);
	Motor_PWM_PWM_C(uC);
	Motor_PWM_PWM_D(uD);
}

//input function
