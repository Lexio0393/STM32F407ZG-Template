#include "bsp_timer.h"

void BSP_TIM2_Init(void)	//5ms @168Mhz While AHB1 is 84Mhz 
{
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimBaseInitStructure.TIM_Period = 5000 - 1;
	TIM_TimBaseInitStructure.TIM_Prescaler = 84 - 1;
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimBaseInitStructure);
	
	//优先级待考虑修改
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM2_Start(void)
{ 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void BSP_TIM5_Init(void)	//10ms
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84 - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;	
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_ARRPreloadConfig(TIM5, ENABLE);
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
	
	//优先级待考虑修改	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM5_Start(void)
{	 
	TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM5, ENABLE);
}

void BSP_Timer_Init(void)
{
	BSP_TIM2_Init();
	BSP_TIM5_Init();
	TIM2_Start();
	TIM5_Start();
}
