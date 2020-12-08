#include "bsp_dt7.h"

volatile unsigned char sbus_rx_buffer[2][RC_FRAME_LENGTH]; //double sbusrx buffer to save data

static RC_Ctl_t RC_CtrlData;

void RC_Init(void)
{
	/* -------------- Enable Module Clock Source ----------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3, GPIO_AF_USART2);
	/* -------------- Configure GPIO ---------------------------------------*/
  {
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	  USART_DeInit(USART2);
	  USART_InitStructure.USART_BaudRate = 100000;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_Even;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_Init(USART2,&USART_InitStructure);
	  
	  USART_Cmd(USART2,ENABLE);
	  USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
  }
  /* -------------- Configure NVIC ---------------------------------------*/
  {
	  NVIC_InitTypeDef NVIC_InitStructure;
	  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
  }
  /* -------------- Configure DMA -----------------------------------------*/
  {
	  DMA_InitTypeDef DMA_InitStructure;
	  DMA_DeInit(DMA1_Stream5);
	  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR);
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sbus_rx_buffer[0][0];
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	  DMA_InitStructure.DMA_BufferSize = RC_FRAME_LENGTH;
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	  DMA_DoubleBufferModeConfig(DMA1_Stream5,(uint32_t)&sbus_rx_buffer[1][0],DMA_Memory_0); //first used memory configuration
	  DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);
	  DMA_Init(DMA1_Stream5,&DMA_InitStructure);
	  USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); //usart rx idle interrupt enabled
	  DMA_Cmd(DMA1_Stream5,ENABLE);
  }
}

void DJI_DT7_SerialIsr(void)
{
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		//clear the idle pending flag
		(void)USART2->SR;
		(void)USART2->DR;
		
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA1_Stream5) == 0)
		{
			DMA_Cmd(DMA1_Stream5, DISABLE);
			DMA1_Stream5->NDTR = (uint16_t)RC_FRAME_LENGTH; //relocate the dma memory pointer to the beginning position
			DMA1_Stream5->CR |= (uint32_t)(DMA_SxCR_CT); 		//enable the current selected memory is Memory 1
			DMA_Cmd(DMA1_Stream5, ENABLE);
			
			if(DMA_GetCurrDataCounter(DMA1_Stream5) == 0) //ensure received complete frame data.
			{
				RemoteDataProcess((uint8_t*)sbus_rx_buffer[0]);
			}
		}
		//Target is Memory1
		else
		{
			DMA_Cmd(DMA1_Stream5, DISABLE);
			DMA1_Stream5->NDTR = (uint16_t)RC_FRAME_LENGTH; //relocate the dma memory pointer to the beginning position
			DMA1_Stream5->CR &= ~(uint32_t)(DMA_SxCR_CT); //enable the current selected memory is Memory 0
			DMA_Cmd(DMA1_Stream5, ENABLE);
			
			if(DMA_GetCurrDataCounter(DMA1_Stream5) == 0)
			{
				RemoteDataProcess((uint8_t*)sbus_rx_buffer[1]);
			}
		}
	} 
}

void RemoteDataProcess(uint8_t *pData)
{
  if(pData == NULL)
  {
		return;
  }

  RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
  RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5))& 0x07FF;
  RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF;
  RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) &0x07FF;
  
  RC_CtrlData.rc.s1  = ((pData[5] >> 4) & 0x000C) >> 2;
  RC_CtrlData.rc.s2  = ((pData[5] >> 4) & 0x0003);
  
  RC_CtrlData.mouse.x = ((int16_t)pData[6])  | ((int16_t)pData[7] << 8);
  RC_CtrlData.mouse.y = ((int16_t)pData[8])  | ((int16_t)pData[9] << 8);
  RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);
  
  RC_CtrlData.mouse.press_l = pData[12];
  RC_CtrlData.mouse.press_r = pData[13];
  RC_CtrlData.key.v = ((int16_t)pData[14]);	// | ((int16_t)pData[15] << 8);
  //your control code бн
}
		