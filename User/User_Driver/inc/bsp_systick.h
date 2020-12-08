#ifndef _BSP_SYSTICK_
#define _BSP_SYSTICK_

#include "stm32f4xx.h"

void BSP_SystickInit(uint32_t SysFreq);
void Delay_us(uint32_t nus);
void Delay_ms(uint32_t nms);

#endif
