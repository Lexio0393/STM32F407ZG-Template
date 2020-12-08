#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "stm32f4xx.h"
#include "stm32f4xx_can.h"

void CAN_Config(CAN_TypeDef *CANx,
		uint32_t CAN_BaudRate,
		GPIO_TypeDef *GPIOx,
		uint16_t CAN_RxPin,
		uint16_t CAN_TxPin);

void BSP_CAN_Init(void);

uint8_t CAN_RxMsg(CAN_TypeDef *CANx,
		uint32_t *StdId,
		uint8_t	 *buf,
		uint8_t  *len);

uint8_t CAN_TxMsg(CAN_TypeDef *CANx,
		uint32_t *StdId,
		uint8_t  *Msg);

#endif
