#include "bsp_09s.h"

uint8_t  SBUS_MsgPack[25];
uint16_t SBUS_ChanelVal[16];

const uint16_t Remote_MinVal = 64;
const uint16_t Remote_MidVal = 1024;
const uint16_t Remote_MaxVal = 1984;
const uint16_t Remote_Deadband = 40;

const uint16_t Remote_SW0_Val = 0x0155;
const uint16_t Remote_SW1_Val = 0x0400;
const uint16_t Remote_SW2_Val = 0x06AA;

Remote_t Remote = {0};

void SBUS_Encode(void);
void SBUS_Decode(void);

void Remote_DeInit(void)
{
	Remote.LX = 0;
	Remote.LY = 0;
	Remote.RX = 0;
	Remote.RY = 0;

	Remote.B  = 0;
	Remote.F  = 0;
	Remote.E  = 0;	
	
	Remote.VA = 0;
	Remote.VB = 0;
}

int16_t Remote_GetChanalValue(RemoteChanel_TypeDef RemoteChanel)
{
	static uint16_t PulseWidth;
	
	if((uint8_t)RemoteChanel < 9)
	{
		PulseWidth = SBUS_ChanelVal[(uint8_t)RemoteChanel];
	}
	
	switch ((uint8_t)RemoteChanel)
	{
		case Remote_RX:
		case Remote_RY:
		case Remote_LY:
		case Remote_LX:
			
				if(PulseWidth > Remote_MidVal + Remote_Deadband)
				{
					return (int16_t)PulseWidth - Remote_MidVal - Remote_Deadband;
				}
				if(PulseWidth < Remote_MidVal - Remote_Deadband)
				{
					return (int16_t)0 - (Remote_MidVal - Remote_Deadband - PulseWidth);
				}	
				return 0;
  
		case Remote_B:
		case Remote_F:
		case Remote_E:
		 
				if(PulseWidth == Remote_SW0_Val)
					return Remote_SW0;
				if(PulseWidth == Remote_SW1_Val)
					return Remote_SW1;
				if(PulseWidth == Remote_SW2_Val)
					return Remote_SW2;
				return Remote_SWErr;
	
    case Remote_VA:
    case Remote_VB:
			return (int16_t)PulseWidth - Remote_MinVal;
	}
	
	return 0xFFFF >> 1;
}

uint16_t Remote_GetChanalPulse(uint8_t Chanel)
{
	if(Chanel < 9)
		return SBUS_ChanelVal[Chanel];
	return 0;
}

void Remote_SerialIsr(void)
{
	static uint8_t Char;
	static uint8_t RxState = 0, RxDataIndex = 0;
	if(USART_GetFlagStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Char = USART_ReceiveData(USART2);
		switch(RxState)
		{
			case 0:											//还未检测到起始标志，开始匹配起始标志
				if(Char == 0x0F)
				{
					RxState++;
					SBUS_MsgPack[0] = Char;
					RxDataIndex = 1;
				}
				else
					RxState = 0;
				break;
			case 1:											//起始标志匹配，开始接收原始数据
				SBUS_MsgPack[RxDataIndex] = Char;
				RxDataIndex++;
				if(RxDataIndex >= 23)
				{
					RxDataIndex = 0;
					RxState++;
				}
				break;
			case 2:											//数据已经接收完毕，开始匹配结束标志第一字节
					SBUS_MsgPack[23] = Char;
					RxState++;
				break;
			case 3:											//结束标志第一字节已匹配，开始匹配结束标志第二字节
				if(Char == 0x00)
				{
					SBUS_Decode();
					SBUS_MsgPack[24] = 0x00;
				}
				RxState = 0;
				break;
			default:
				RxState = 0;
		}
	}
}

/*
 ********************************************************************************
                        SBUS Encode & Decode Function
 ********************************************************************************
 */

void SBUS_Encode(void)
{
	SBUS_MsgPack[0]  = 0x0F; 
	SBUS_MsgPack[1]  = (uint8_t) ((SBUS_ChanelVal[0]	& 0x07FF));
	SBUS_MsgPack[2]  = (uint8_t) ((SBUS_ChanelVal[0]	& 0x07FF) >> 8	| (SBUS_ChanelVal[1]	& 0x07FF) << 3);
	SBUS_MsgPack[3]  = (uint8_t) ((SBUS_ChanelVal[1]	& 0x07FF) >> 5	| (SBUS_ChanelVal[2]	& 0x07FF) << 6);
	SBUS_MsgPack[4]  = (uint8_t) ((SBUS_ChanelVal[2]	& 0x07FF) >> 2);
	SBUS_MsgPack[5]  = (uint8_t) ((SBUS_ChanelVal[2]	& 0x07FF) >> 10	| (SBUS_ChanelVal[3]	& 0x07FF) << 1);
	SBUS_MsgPack[6]  = (uint8_t) ((SBUS_ChanelVal[3]	& 0x07FF) >> 7	| (SBUS_ChanelVal[4]	& 0x07FF) << 4);
	SBUS_MsgPack[7]  = (uint8_t) ((SBUS_ChanelVal[4]	& 0x07FF) >> 4	| (SBUS_ChanelVal[5]	& 0x07FF) << 7);
	SBUS_MsgPack[8]  = (uint8_t) ((SBUS_ChanelVal[5]	& 0x07FF) >> 1);
	SBUS_MsgPack[9]  = (uint8_t) ((SBUS_ChanelVal[5]	& 0x07FF) >> 9	| (SBUS_ChanelVal[6]	& 0x07FF) << 2);
	SBUS_MsgPack[10] = (uint8_t) ((SBUS_ChanelVal[6]	& 0x07FF) >> 6	| (SBUS_ChanelVal[7]	& 0x07FF) << 5);
	SBUS_MsgPack[11] = (uint8_t) ((SBUS_ChanelVal[7]	& 0x07FF) >> 3);
	SBUS_MsgPack[12] = (uint8_t) ((SBUS_ChanelVal[8]	& 0x07FF));
	SBUS_MsgPack[13] = (uint8_t) ((SBUS_ChanelVal[8]	& 0x07FF) >> 8	| (SBUS_ChanelVal[9]	& 0x07FF) << 3);
	SBUS_MsgPack[14] = (uint8_t) ((SBUS_ChanelVal[9]	& 0x07FF) >> 5	| (SBUS_ChanelVal[10]	& 0x07FF) << 6);  
	SBUS_MsgPack[15] = (uint8_t) ((SBUS_ChanelVal[10]	& 0x07FF) >> 2);
	SBUS_MsgPack[16] = (uint8_t) ((SBUS_ChanelVal[10]	& 0x07FF) >> 10	| (SBUS_ChanelVal[11]	& 0x07FF) << 1);
	SBUS_MsgPack[17] = (uint8_t) ((SBUS_ChanelVal[11]	& 0x07FF) >> 7	| (SBUS_ChanelVal[12]	& 0x07FF) << 4);
	SBUS_MsgPack[18] = (uint8_t) ((SBUS_ChanelVal[12]	& 0x07FF) >> 4	| (SBUS_ChanelVal[13]	& 0x07FF) << 7);
	SBUS_MsgPack[19] = (uint8_t) ((SBUS_ChanelVal[13]	& 0x07FF) >> 1);
	SBUS_MsgPack[20] = (uint8_t) ((SBUS_ChanelVal[13]	& 0x07FF) >> 9	| (SBUS_ChanelVal[14]	& 0x07FF) << 2);
	SBUS_MsgPack[21] = (uint8_t) ((SBUS_ChanelVal[14]	& 0x07FF) >> 6	| (SBUS_ChanelVal[15]	& 0x07FF) << 5);
	SBUS_MsgPack[22] = (uint8_t) ((SBUS_ChanelVal[15]	& 0x07FF) >> 3);
	SBUS_MsgPack[23] = 0x00;
	SBUS_MsgPack[24] = 0X00;
}

void SBUS_Decode(void)
{
	SBUS_ChanelVal[0]  = ((SBUS_MsgPack[1]		| (SBUS_MsgPack[2]&0x07) << 8)	& 0x07FF);
	SBUS_ChanelVal[1]  = ((SBUS_MsgPack[2] >> 3	| SBUS_MsgPack[3] << 5)	& 0x07FF);
	SBUS_ChanelVal[2]  = ((SBUS_MsgPack[3] >> 6	| SBUS_MsgPack[4] << 2 | SBUS_MsgPack[5] << 10)	& 0x07FF);
	SBUS_ChanelVal[3]  = ((SBUS_MsgPack[5] >> 1	| SBUS_MsgPack[6] << 7)	& 0x07FF);
	SBUS_ChanelVal[4]  = ((SBUS_MsgPack[6] >> 4	| SBUS_MsgPack[7] <<4)	& 0x07FF);
	SBUS_ChanelVal[5]  = ((SBUS_MsgPack[7] >> 7	| SBUS_MsgPack[8] << 1 | SBUS_MsgPack[9] << 9)	& 0x07FF);
	SBUS_ChanelVal[6]  = ((SBUS_MsgPack[9] >> 2	| SBUS_MsgPack[10] << 6)	& 0x07FF);
	SBUS_ChanelVal[7]  = ((SBUS_MsgPack[10] >> 5	| SBUS_MsgPack[11] << 3)	& 0x07FF);
	SBUS_ChanelVal[8]  = ((SBUS_MsgPack[12]		| SBUS_MsgPack[13] << 8)	& 0x07FF);
	SBUS_ChanelVal[9]  = ((SBUS_MsgPack[13] >> 3	| SBUS_MsgPack[14]<<5)	& 0x07FF);
	SBUS_ChanelVal[10] = ((SBUS_MsgPack[14] >> 6	| SBUS_MsgPack[15]<<2 | SBUS_MsgPack[16] << 10)	& 0x07FF);
	SBUS_ChanelVal[11] = ((SBUS_MsgPack[16] >> 1	| SBUS_MsgPack[17]<<7)	& 0x07FF);
	SBUS_ChanelVal[12] = ((SBUS_MsgPack[17] >> 4	| SBUS_MsgPack[18]<<4)	& 0x07FF);
	SBUS_ChanelVal[13] = ((SBUS_MsgPack[18] >> 7	| SBUS_MsgPack[19]<<1 | SBUS_MsgPack[20]<<9)	& 0x07FF);
	SBUS_ChanelVal[14] = ((SBUS_MsgPack[20] >> 2	| SBUS_MsgPack[21]<<6)	& 0x07FF);
	SBUS_ChanelVal[15] = ((SBUS_MsgPack[21] >> 5	| SBUS_MsgPack[22]<<3)	& 0x07FF);
}
