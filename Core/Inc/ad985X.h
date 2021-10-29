//
// Created by jkhu29 on 2021/7/9.
//

#ifndef __AD985x_H
#define __AD985x_H

#include "gpio.h"

//void AD985x_Init(void);
void AD985x_Reset_Serail(void);
void AD985x_Set_Frequency(unsigned char W0,unsigned long Fre);


#endif // __AD985x_H
