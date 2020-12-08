#include "bsp_systick.h"
//本文件用于初始化延时函数

static uint32_t fac_us = 0;
static uint32_t fac_ms = 0;

void BSP_SystickInit(uint32_t SysFreq)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us = SysFreq / 8;
	fac_ms = fac_us * 1000;
}

void Delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD = nus * fac_us;
	SysTick->VAL  = 0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	
	
	do
	{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1 << 16)));
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0x00;
}

void Delay_xms(uint32_t nms)
{
	uint32_t temp;
	SysTick->LOAD = nms * fac_ms;
	SysTick->VAL  = 0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	
	
	do
	{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1 << 16)));
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0x00;
}

void Delay_ms(uint32_t nms)
{
	uint32_t repeat = nms / 540;
	uint32_t remain = nms % 540;
	while(repeat)
	{
		Delay_xms(540);
		repeat--;
	}
	if(remain)
		Delay_xms(remain);
}
