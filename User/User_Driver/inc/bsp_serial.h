#ifndef _BSP_SERIAL_H
#define _BSP_SERIAL_H

#include "stm32f4xx.h"

#define Serial_TypeDef USART_TypeDef

#define Serial1	USART1
#define Serial2 USART2
#define Serial3 USART3
#define Serial6 USART6

#define Periph_Serial1_GPIO		RCC_AHB1Periph_GPIOA
#define GPIO_Port_Serial1_Tx	GPIOA
#define GPIO_Pin_Serial1_Tx		GPIO_Pin_9
#define PinSource_Serial1_Tx	GPIO_PinSource9
#define GPIO_Port_Serial1_Rx	GPIOA
#define GPIO_Pin_Serial1_Rx		GPIO_Pin_10
#define PinSource_Serial1_Rx	GPIO_PinSource10

#define Periph_Serial2_GPIO		RCC_AHB1Periph_GPIOA
#define GPIO_Port_Serial2_Tx	GPIOA
#define GPIO_Pin_Serial2_Tx		GPIO_Pin_2
#define PinSource_Serial2_Tx	GPIO_PinSource2
#define GPIO_Port_Serial2_Rx	GPIOA
#define GPIO_Pin_Serial2_Rx		GPIO_Pin_3
#define PinSource_Serial2_Rx	GPIO_PinSource3

#define Periph_Serial3_GPIO		RCC_AHB1Periph_GPIOD
#define GPIO_Port_Serial3_Tx	GPIOD
#define GPIO_Pin_Serial3_Tx		GPIO_Pin_8
#define PinSource_Serial3_Tx	GPIO_PinSource8
#define GPIO_Port_Serial3_Rx	GPIOD
#define GPIO_Pin_Serial3_Rx		GPIO_Pin_9
#define PinSource_Serial3_Rx	GPIO_PinSource9

#define Periph_Serial6_GPIO		RCC_AHB1Periph_GPIOC
#define GPIO_Port_Serial6_Tx	GPIOC
#define GPIO_Pin_Serial6_Tx		GPIO_Pin_6
#define PinSource_Serial6_Tx	GPIO_PinSource6
#define GPIO_Port_Serial6_Rx	GPIOC
#define GPIO_Pin_Serial6_Rx		GPIO_Pin_7
#define PinSource_Serial6_Rx	GPIO_PinSource7


void BSP_Serial_Init(void);

void Serial_SendByte(Serial_TypeDef *Serialx, uint8_t Data);
void Serial_SendArray(Serial_TypeDef *Serialx, uint8_t *Array, uint16_t Length);
void Serial_SendString(Serial_TypeDef *Serialx, uint8_t *String);

#endif
