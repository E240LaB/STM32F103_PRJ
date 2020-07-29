#include "controlLaw.h"

/* Change your control method here. */
void (*controlMethod)(void) = system_controlLAW;

void system_controlLAW(void){
	balance_y_control = controlLaw_LQR_y();
	steer_control =controlLaw_P_Diff();
	balance_x_control =controlLaw_P_x();
}
float controlLaw_LQR_y(void) {
	float uy = Angle_KP*Angle_Roll + Angle_Rate_KD*Gyro_Roll + Postion_y_KP*postion_y_error  + Velocity_y_KD*Robot_Velocity_y;
  return uy;
}

float controlLaw_P_Diff(void) {
  float ut = Diff_angle_KP*Robot_Diff_angle_error;
  return ut;
}

float controlLaw_P_x(void) {
  float ux = 0;//Diff_angle_KP*Robot_Diff_angle_error;
  return ux;
}
