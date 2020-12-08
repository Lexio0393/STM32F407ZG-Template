#include "bsp_main.h"

/* ���ļ����ڰ��������ʼ�� */

void BSP_Init(void)
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	BSP_SystickInit(168);
	
	BSP_IO_Init();
	
	Delay_ms(100);
	
	BSP_CAN_Init();
	
	BSP_Serial_Init();
	BSP_Timer_Init();
}
