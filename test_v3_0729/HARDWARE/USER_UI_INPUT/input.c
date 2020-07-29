#include "input.h"

//input function
void Robot_cmd() {
	
	if (running_count <= 2000) {
		_postion_y  = 0.00;
		_postion_x  = 0.00;
		_Diff_angle =0.00;
	}
//	else if (running_count <= 20500)
//	{
//		postion_y = 1.00;
//		Diff_angle = 0.00;
//	}else{
//			postion_y = 0.00;
//		Diff_angle = 0.00;
//	}
//	else if (running_count <= 4500)
//	{
//		postion_y = 0.00;
//		Diff_angle = 0.25;
//	}
	postion_y_cmd = postion_y_cmd + _postion_y;
	postion_x_cmd = postion_x_cmd + _postion_x;
	postion_y_error = Robot_Position_y - postion_y_cmd;
	postion_x_error = Robot_Position_x - postion_x_cmd;
	
	Robot_Diff_angle_cmd = Robot_Diff_angle_cmd + _Diff_angle;
	Robot_Diff_angle_error = Robot_Diff_angle_cmd - Robot_Diff_angle;
}

void Get_Robot_Position() {
	denA= thetaA-othetaA;
	othetaA = thetaA;
	thetaB = thetaB-Read_Encoder(3);
	denB= thetaB-othetaB;
	othetaB = thetaB;
	thetaC = thetaC+Read_Encoder(4);
	denC= thetaC-othetaC;
	othetaC = thetaC;
	thetaD = thetaD-Read_Encoder(5);
	denD= thetaD-othetaD;
	othetaD = thetaD;
	
	Robot_Position_x = Robot_Position_x + (denA - denB - denC + denD) / 4.0;
	Robot_Velocity_x = (denA - denB - denC + denD) / 4.0 / 0.01;
	Robot_Position_y = Robot_Position_y + (denA + denB + denC + denD) / 4.0;
	Robot_Velocity_y = (denA + denB + denC + denD) / 4.0 / 0.01;
	Robot_Diff_angle  = (-thetaA - thetaB + thetaC + thetaD) / 2;	thetaA = thetaA+Read_Encoder(2);
}