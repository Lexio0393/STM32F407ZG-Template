#include "bsp_serial.h"


void BSP_Serial1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO and USART clock */
	RCC_AHB1PeriphClockCmd(Periph_Serial1_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIO_Port_Serial1_Tx, PinSource_Serial1_Tx, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIO_Port_Serial1_Rx, PinSource_Serial1_Rx, GPIO_AF_USART1);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial1_Tx;
	GPIO_Init(GPIO_Port_Serial1_Tx, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial1_Rx;
	GPIO_Init(GPIO_Port_Serial1_Rx, &GPIO_InitStructure);

	/* USART1 configuration ----------------------------------------------------*/
	/* USART1 configured as follows:
		- BaudRate = 115200 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
				- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
				- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
			- Maximum BaudRate that can be achieved when using the Oversampling by 16
				is: (USART APB Clock / 16) 
				Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
				Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
		- Word Length = 8 Bits
		- one Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  Configures the USART2 Peripheral.
  * @param  None
  * @retval None
  */
void BSP_Serial2_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO and USART clock */
	RCC_AHB1PeriphClockCmd(Periph_Serial2_GPIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIO_Port_Serial2_Tx, PinSource_Serial2_Tx, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIO_Port_Serial2_Rx, PinSource_Serial2_Rx, GPIO_AF_USART2);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial2_Tx;
	GPIO_Init(GPIO_Port_Serial2_Tx, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial2_Rx;
	GPIO_Init(GPIO_Port_Serial2_Rx, &GPIO_InitStructure);

	/* USART2 configuration ----------------------------------------------------*/
	/* USART2 configured as follows:
		- BaudRate = 115200 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
				- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
				- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
			- Maximum BaudRate that can be achieved when using the Oversampling by 16
				is: (USART APB Clock / 16) 
				Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
				Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
		- Word Length = 8 Bits
		- one Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 100000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_2;
	USART_InitStructure.USART_Parity = USART_Parity_Even;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStructure);	//¸ù¾ÝÒ£¿ØÆ÷´ýÐÞ¸Ä
//		USART_InitStructure.USART_BaudRate = 115200;
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;
//		USART_InitStructure.USART_Parity = USART_Parity_No;
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//		USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable USART */
	USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  Configures the USART3 Peripheral.
  * @param  None
  * @retval None
  */
void BSP_Serial3_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO and USART clock */
	RCC_AHB1PeriphClockCmd(Periph_Serial3_GPIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIO_Port_Serial3_Tx, PinSource_Serial3_Tx, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIO_Port_Serial3_Rx, PinSource_Serial3_Rx, GPIO_AF_USART3);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial3_Tx;
	GPIO_Init(GPIO_Port_Serial3_Tx, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial3_Rx;
	GPIO_Init(GPIO_Port_Serial3_Rx, &GPIO_InitStructure);

	/* USART3 configuration ----------------------------------------------------*/
	/* USART3 configured as follows:
		- BaudRate = 115200 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
				- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
				- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
			- Maximum BaudRate that can be achieved when using the Oversampling by 16
				is: (USART APB Clock / 16) 
				Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
				Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
		- Word Length = 8 Bits
		- one Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable USART */
	USART_Cmd(USART3, ENABLE);
}

void BSP_Serial6_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO and USART clock */
	RCC_AHB1PeriphClockCmd(Periph_Serial6_GPIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIO_Port_Serial6_Tx, PinSource_Serial6_Tx, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIO_Port_Serial6_Rx, PinSource_Serial6_Rx, GPIO_AF_USART6);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial6_Tx;
	GPIO_Init(GPIO_Port_Serial6_Tx, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Serial6_Rx;
	GPIO_Init(GPIO_Port_Serial6_Rx, &GPIO_InitStructure);

	/* USART1 configuration ----------------------------------------------------*/
	/* USART1 configured as follows:
		- BaudRate = 115200 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
				- (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
				- (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
			- Maximum BaudRate that can be achieved when using the Oversampling by 16
				is: (USART APB Clock / 16) 
				Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
				Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
		- Word Length = 8 Bits
		- one Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable USART */
	USART_Cmd(USART6, ENABLE);
}

void BSP_Serial_Init()
{
	BSP_Serial1_Init();
	BSP_Serial2_Init();
	BSP_Serial3_Init();
	BSP_Serial6_Init();
}


void Serial_SendByte(Serial_TypeDef *Serialx, uint8_t Data)
{
	while(USART_GetFlagStatus(Serialx, USART_FLAG_TC) != SET);
	USART_SendData(Serialx, Data);
}

void Serial_SendArray(Serial_TypeDef *Serialx, uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for(i = 0; i < Length; i++)
		Serial_SendByte(Serialx, Array[i]);
}

void Serial_SendString(Serial_TypeDef *Serialx, uint8_t *String)
{
	uint16_t i = 0;
	while(String[i] != '\0')
	{
		Serial_SendByte(Serialx, String[i]);
		i++;
	}
}
