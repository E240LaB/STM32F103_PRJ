#include "test_fuction.h"

void  test_uart(void){
	printf("hello world\n");
	delay_ms(100);
}
	
void  test_pwm(void){
	int i=0;

	for(i=-7200;i<=7200;i=i+360){
		Motor_PWM_PWM_A(i);
		Motor_PWM_PWM_B(i);
    Motor_PWM_PWM_C(i);
    Motor_PWM_PWM_D(i);
		delay_ms(500);
		Motor_stop();
		delay_ms(500);
		printf("power:%d\n",i);
				printf("==============================================================\n");
	}
//	Motor_PWM_PWM_B(7000);
//	Motor_PWM_PWM_C(7000);
//	Motor_PWM_PWM_D(7000);
//	delay_ms(1500);
//	Motor_PWM_PWM_A(-7200);
//	Motor_PWM_PWM_B(-7200);
//	Motor_PWM_PWM_C(-7200);
//	Motor_PWM_PWM_D(-7200);
//	delay_ms(1500);
		Motor_stop();
}
void  test_display_UARTENCODER(int state){
	float motor_KP=0.1831;
	int ua,ub,uc,ud;
	Get_Robot_Position();
	switch(state){
		case 1:


			printf("===================\n");
			printf("thetaA:%d\t",thetaA);
			printf("thetaB:%d\n",thetaB);
			printf("thetaC:%d\t",thetaC);
			printf("thetaD:%d\n",thetaD);
			printf("===================\n");
		break;
		
		case 2:
			errorA = thetaA_cmd-thetaA;
		  errorB = thetaB_cmd-thetaB;
		  errorC = thetaC_cmd-thetaC;
		  errorD = thetaD_cmd-thetaD;
		
		  ua= motor_KP*errorA;
		  ub= motor_KP*errorB;
		  uc= motor_KP*errorC;
		  ud= motor_KP*errorD;
	   	delay_ms(3);

		  Motor_PWM_PWM_A(ua);
			Motor_PWM_PWM_B(ub);
		  Motor_PWM_PWM_C(uc);
			Motor_PWM_PWM_D(ud);
		
			printf("===================\n");
		  printf("thetaA_cmd:%f\t",thetaA_cmd);printf("thetaA:%d\n",thetaA);
			printf("thetaB_cmd:%f\t",thetaB_cmd);printf("thetaB:%d\n",thetaB);
			printf("thetaC_cmd:%f\t",thetaC_cmd);printf("thetaC:%d\n",thetaC);
			printf("thetaD_cmd:%f\t",thetaD_cmd);printf("thetaD:%d\n",thetaD);
		  printf("errorA:%f\t",errorA);printf("errorB:%f\n",errorB);
		  printf("errorC:%f\t",errorC);printf("errorD:%f\n",errorD);
			printf("ua:%d,ub:%d,uc:%d,ud:%d\n",ua,ub,uc,ud);
			printf("===================\n");
			
		break;
		
		case 3:

			printf("===================\n");
		  printf("Robot_Position_x:%f\t",Robot_Position_x);
		  printf("Robot_Velocity_x:%f\n",Robot_Velocity_x);
		  printf("Robot_Position_y:%f\t",Robot_Position_y);
		  printf("Robot_Velocity_y:%f\n",Robot_Velocity_y);
		  printf("Robot_Diff_angle:%f\n",Robot_Diff_angle);
			printf("===================\n");
		
		break;
	}
}
void  test_display_MPU6050_DMP(){
		printf("===================\n");	
		printf("Angle_Pitch=%f\t",Angle_Pitch);printf("Angle_Roll=%f\t",Angle_Roll);printf("Angle_Yaw=%f\n",Angle_Yaw);
		printf("Gyro_Pitch=%f\t",Gyro_Pitch);printf("Gyro_Roll=%f\t",Gyro_Roll);printf("Gyro_Yaw=%f\n",Gyro_Yaw);
		printf("===================\n");
}
