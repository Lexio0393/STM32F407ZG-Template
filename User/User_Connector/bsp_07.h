#ifndef _BSP_07_H
#define _BSP_07_H

#include "stm32f4xx.h"

typedef enum
{
	  Remote_RX = (uint8_t)0x00,
    Remote_RY = (uint8_t)0x01,
    Remote_LY = (uint8_t)0x02,
    Remote_LX = (uint8_t)0x03,
	
		Remote_T1 = (uint8_t)0x04,
    Remote_S1 = (uint8_t)0x05,
	
		Remote_VA	= (uint8_t)0x06,
	
		Remote_S2 = (uint8_t)0x07,
		Remote_T2 = (uint8_t)0x08,
}RemoteChanel_TypeDef;

typedef struct
{
    int16_t RX;
    int16_t RY;
    int16_t LY;
    int16_t LX;
    
    int16_t T1;
    int16_t S1;
    int16_t T2;
		int16_t S2;
	
    int16_t VA;
}Remote_t;

typedef enum
{
    Remote_SW0   = (int16_t)0,
    Remote_SW1   = (int16_t)1,
    Remote_SW2   = (int16_t)2,
    Remote_SWErr = (int16_t)3,
}Remote_SwitchStatus_TypeDef;

void Remote_DeInit(void);
void Remote_SerialIsr(void);
int16_t Remote_GetChanalValue(RemoteChanel_TypeDef RemoteChanel);
uint16_t Remote_GetChanalPulse(uint8_t Chanel);

#endif
