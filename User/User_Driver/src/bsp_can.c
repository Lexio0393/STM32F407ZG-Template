#include "bsp_can.h"
#include "misc.h"

//#include "stm32f4xx_gpio.h"
//#include "String.h"
//#include "bsp_io.h"
//#include "bsp_serial.h"

void CAN_Config(CAN_TypeDef *CANx,
				uint32_t CAN_BaudRate,
				GPIO_TypeDef *GPIOx,
				uint16_t CAN_RxPin,
				uint16_t CAN_TxPin)
{
	GPIO_InitTypeDef 		GPIO_InitStructure;
	CAN_InitTypeDef	 		CAN_InitStructure;
	CAN_FilterInitTypeDef	CAN_FilterInitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
	
	uint8_t CAN_RxSource = 0;
	uint8_t CAN_TxSource = 0;
	uint8_t GPIO_AF_CANx = 0;
	
	/* ȷ��CAN_RxPin */
	switch (CAN_RxPin)
	{
		case GPIO_Pin_11:
		{
			CAN_RxSource = GPIO_PinSource11;
			break;
		}
		case GPIO_Pin_5:
		{
			CAN_RxSource = GPIO_PinSource5;
			break;
		}
		
		default:
			break;
	}

	/* ȷ��CAN_TxPin */
	switch (CAN_TxPin)
	{
		case GPIO_Pin_12:
		{
			CAN_TxSource = GPIO_PinSource12;
			break;
		}
		case GPIO_Pin_6:
		{
			CAN_TxSource = GPIO_PinSource6;
			break;
		}
		
		default:
			break;
	}
	/* CANx�������� */
	
	switch ((uint32_t)CANx)
	{
	case CAN1_BASE:
	{
		GPIO_AF_CANx = GPIO_AF_CAN1;
		CAN_FilterInitStructure.CAN_FilterNumber = 0; //Filter 0
		//NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		break;
	}
	case CAN2_BASE:
	{
		GPIO_AF_CANx = GPIO_AF_CAN2;
		CAN_FilterInitStructure.CAN_FilterNumber = 14; //Filter 1		//���޸�
		//NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
		break;
	}

	default:
		break;
	}	
	
	/* GPIOxʱ��ʹ�� */
	switch ((uint32_t)GPIOx)
	{
		case GPIOA_BASE:
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			break;
		}
		case GPIOB_BASE:
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			break;
		}
		default:
			break;
	}	
	
	/* GPIO�ڳ�ʼ�� */
	GPIO_InitStructure.GPIO_Pin = CAN_RxPin | CAN_TxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;			//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
	GPIO_Init(GPIOx, &GPIO_InitStructure);		

	/* ���Ÿ���ΪCAN */
	GPIO_PinAFConfig(GPIOx, CAN_RxSource, GPIO_AF_CANx);
	GPIO_PinAFConfig(GPIOx, CAN_TxSource, GPIO_AF_CANx);
	
	/* CANx�Ĵ�����ʼ�� */
	CAN_DeInit(CANx);
	
	/* CAN Cell Init */
	CAN_InitStructure.CAN_TTCM = DISABLE;					//��ʱ�䴥��ͨ��ģ#ʽ
	CAN_InitStructure.CAN_ABOM = ENABLE;					//����Զ����߹���
	CAN_InitStructure.CAN_AWUM = DISABLE;					//˯��ģʽͨ��������ѣ����CAN->MCR��SLEEPλ��
	CAN_InitStructure.CAN_NART = DISABLE;					//��ֹ�����Զ�����
	CAN_InitStructure.CAN_RFLM = DISABLE;					//���Ĳ�����,�µĸ��Ǿɵ�
	CAN_InitStructure.CAN_TXFP = DISABLE;					//���ȼ��ɱ��ı�ʶ������
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;			//ģʽ����
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;				//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq

	/* CAN���������� */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq;										//Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;										//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
	/* CAN Baudrate =APB1_CLK/((CAN_SJW_tq+CAN_BS1_tq+CAN_BS2_tq)*CAN_Prescaler) */
	
	//APB1_CLK = 42000
	switch (CAN_BaudRate)
	{
		case 10:
		{
			CAN_InitStructure.CAN_Prescaler = 300;
			break;
		}
		case 20:
		{
			CAN_InitStructure.CAN_Prescaler = 150;
			break;
		}
		case 50:
		{
			CAN_InitStructure.CAN_Prescaler = 60;
			break;
		}
		case 100:
		{
		CAN_InitStructure.CAN_Prescaler = 30;
			break;
		}
		case 125:
		{
			CAN_InitStructure.CAN_Prescaler = 24;
			break;
		}
		case 250:
		{
			CAN_InitStructure.CAN_Prescaler = 12;
			break;
		}
		case 500:
		{
			CAN_InitStructure.CAN_Prescaler = 6;
			break;
		}
		case 1000:
		{
			CAN_InitStructure.CAN_Prescaler = 3;
			break;
		}
	
		default:
			break;
	}
	
	CAN_Init(CANx, &CAN_InitStructure);
	
	/* CAN�˲�����ʼ�� */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 		//32 Bit
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				 		//32 Bis ID
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000; 					//32 Bit Mask
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; 					//activate Filter
	CAN_FilterInit(&CAN_FilterInitStructure);			   					//intialize Filter

	/* Enable FIFO 0 message pending Interrupt */

	switch ((uint32_t)CANx)
	{
		case CAN1_BASE:
		{
			NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
		
			NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure); 
			break;
		}
		case CAN2_BASE:
		{
			NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
		
			NVIC_InitStructure.NVIC_IRQChannel = CAN2_TX_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure); 
			break;
		}
	
		default:
			break;
	}
	
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CANx,CAN_IT_TME ,ENABLE);
}


void BSP_CAN_Init(void)
{
	CAN_Config(CAN1, 1000, GPIOA, GPIO_Pin_11, GPIO_Pin_12);
	CAN_Config(CAN2, 1000, GPIOB, GPIO_Pin_5 , GPIO_Pin_6 );
}
