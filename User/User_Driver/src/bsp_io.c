#include "bsp_io.h"
//本文件用于流水灯及蜂鸣器的初始化

/* LED Interface */
void LED0_On(void)
{
	GPIO_ResetBits(GPIO_Port_LED0, GPIO_Pin_LED0);
}
void LED0_Off(void)
{
	GPIO_SetBits(GPIO_Port_LED0, GPIO_Pin_LED0);
}
void LED0_Toggle(void)
{
	GPIO_ToggleBits(GPIO_Port_LED0, GPIO_Pin_LED0);
}

void LED1_On(void)
{
	GPIO_ResetBits(GPIO_Port_LED1, GPIO_Pin_LED1);
}
void LED1_Off(void)
{
	GPIO_SetBits(GPIO_Port_LED1, GPIO_Pin_LED1);
}
void LED1_Toggle(void)
{
	GPIO_ToggleBits(GPIO_Port_LED1, GPIO_Pin_LED1);
}

void LED2_On(void)
{
	GPIO_ResetBits(GPIO_Port_LED2, GPIO_Pin_LED2);
}
void LED2_Off(void)
{
	GPIO_SetBits(GPIO_Port_LED2, GPIO_Pin_LED2);
}
void LED2_Toggle(void)
{
	GPIO_ToggleBits(GPIO_Port_LED2, GPIO_Pin_LED2);
}

void LED3_On(void)
{
	GPIO_ResetBits(GPIO_Port_LED3, GPIO_Pin_LED3);
}
void LED3_Off(void)
{
	GPIO_SetBits(GPIO_Port_LED3, GPIO_Pin_LED3);
}
void LED3_Toggle(void)
{
	GPIO_ToggleBits(GPIO_Port_LED3, GPIO_Pin_LED3);
}

/* Beep Interface */
void Beep_On(void)
{
	GPIO_SetBits(GPIO_Port_Beep, GPIO_Pin_Beep);
}
void Beep_Off(void)
{
	GPIO_ResetBits(GPIO_Port_Beep, GPIO_Pin_Beep);
}


void BSP_LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(Periph_GPIO_LED0, ENABLE);
//	RCC_AHB1PeriphClockCmd(Periph_GPIO_LED1, ENABLE);
//	RCC_AHB1PeriphClockCmd(Periph_GPIO_LED2, ENABLE);
//	RCC_AHB1PeriphClockCmd(Periph_GPIO_LED3, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode 	 = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_LED0;
	GPIO_Init(GPIO_Port_LED0, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_LED1;
	GPIO_Init(GPIO_Port_LED1, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_LED2;
	GPIO_Init(GPIO_Port_LED2, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_LED3;
	GPIO_Init(GPIO_Port_LED3, &GPIO_InitStruct);
	
	LED0_Off();
	LED1_Off();
	LED2_Off();
	LED3_Off();
}

void BSP_Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(Periph_GPIO_Beep, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_Beep;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIO_Port_Beep, &GPIO_InitStruct);

	Beep_Off();
}

void BSP_Valve_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Push;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIO_Port_Push, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Pull;
	GPIO_Init(GPIO_Port_Pull, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIO_Port_Push, GPIO_Pin_Push);
	GPIO_ResetBits(GPIO_Port_Pull, GPIO_Pin_Pull);
}
void BSP_IO_Init(void)
{
	BSP_LED_Init();
	BSP_Beep_Init();
	BSP_Valve_Init();
}
