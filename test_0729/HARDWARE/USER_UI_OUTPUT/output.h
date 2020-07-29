#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "system_init.h"
//output function
void Motion_Transfer(int ux, int uy, int ut);
void Robot_power_out(int uA, int uB, int uC, int uD);
void Robot_Dir(int mode, int power);
#endif
