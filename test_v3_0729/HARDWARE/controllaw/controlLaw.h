#ifndef _CONTROLLAW_H_
#define _CONTROLLAW_H_

#include "system_init.h"
void  system_controlLAW(void);
float controlLaw_LQR_y(void);
float controlLaw_P_Diff(void);
float controlLaw_P_x(void);
#endif
