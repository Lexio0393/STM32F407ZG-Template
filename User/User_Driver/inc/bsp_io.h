#ifndef _BSP_IO_
#define _BSP_IO_

#include "stm32f4xx.h"

#define Periph_GPIO_LED0	RCC_AHB1Periph_GPIOC
#define GPIO_Port_LED0		GPIOC
#define GPIO_Pin_LED0			GPIO_Pin_0

#define Periph_GPIO_LED1	RCC_AHB1Periph_GPIOC
#define GPIO_Port_LED1		GPIOC
#define GPIO_Pin_LED1		GPIO_Pin_1

#define Periph_GPIO_LED2	RCC_AHB1Periph_GPIOC
#define GPIO_Port_LED2		GPIOC
#define GPIO_Pin_LED2			GPIO_Pin_2

#define Periph_GPIO_LED3	RCC_AHB1Periph_GPIOC
#define GPIO_Port_LED3		GPIOC
#define GPIO_Pin_LED3			GPIO_Pin_3

#define Periph_GPIO_Beep	RCC_AHB1Periph_GPIOD
#define GPIO_Port_Beep		GPIOD
#define GPIO_Pin_Beep			GPIO_Pin_0

#define Periph_GPIO_Cylinder	RCC_AHB1Periph_GPIOD
#define GPIO_Port_Push				GPIOD
#define GPIO_Pin_Push					GPIO_Pin_4
#define GPIO_Port_Pull				GPIOD
#define GPIO_Pin_Pull					GPIO_Pin_5

void BSP_IO_Init(void);

/* LED Interface */
void LED0_On(void);
void LED0_Off(void);
void LED0_Toggle(void);
void LED1_On(void);
void LED1_Off(void);
void LED1_Toggle(void);
void LED2_On(void);
void LED2_Off(void);
void LED2_Toggle(void);
void LED3_On(void);
void LED3_Off(void);
void LED3_Toggle(void);

/* Beep Interface */
void Beep_On(void);
void Beep_Off(void);

#endif
