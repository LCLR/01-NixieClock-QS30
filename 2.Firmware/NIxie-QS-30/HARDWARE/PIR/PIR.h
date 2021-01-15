#ifndef __PIR_H
#define __PIR_H
#include "sys.h"

#define PIR_Sta PBin(15)

void PIR_Init(void);
int GetPIR_Sta(void);


#endif