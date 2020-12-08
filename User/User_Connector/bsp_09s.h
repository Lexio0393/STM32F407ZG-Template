#ifndef _BSP_09S_H
#define _BSP_09S_H

#include "stm32f4xx.h"

/*
 * This Remote Control has 9 channels for you to set
 * The members of the enum variable RemoteChanel can be changed by user
 * It can be changed by the Accessibility channel settings on the Remote Control
 * The joysticks have four channels: RX,RY,LX,LY
 * The dual buttons are A,C,D,E
 * The triple buttons are B and F
 * The Rotate buttons are VA,VB,VC
 * 
 */
typedef enum
{
	  Remote_RX = (uint8_t)0x00,
    Remote_RY = (uint8_t)0x02,
    Remote_LY = (uint8_t)0x01,
    Remote_LX = (uint8_t)0x03,
	
		Remote_B  = (uint8_t)0x08,
    Remote_F  = (uint8_t)0x04,
		Remote_E	= (uint8_t)0x06,
	
		Remote_VA = (uint8_t)0x05,
		Remote_VB = (uint8_t)0x07,
	
//		Remote_A  = (uint8_t)0x08
}RemoteChanel_TypeDef;

/*
 * If you have changed the member of the enum, 
		you must change the member of this struct correspondingly
 */
typedef struct
{
    int16_t RX;
    int16_t RY;
    int16_t LY;
    int16_t LX;
    
    int16_t B;
    int16_t F;
    int16_t E;
	
    int16_t VA;
		int16_t VB;
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
