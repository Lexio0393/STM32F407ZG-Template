#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include "stm32f4xx.h"
#include "arm_math.h"

#include <stdio.h>
#include <math.h>

typedef struct
{
	float a;
	float b;
	float c;
}QudraticFunction;

typedef enum
{
	Sig_Pos  = 0x01,
	Sig_Neg  = 0xFF,
	Sig_Zero = 0x00,
}Signal_TypeDef;

/*
//πÏº£”√
typedef struct
{
	float	x;
	float	y;
}Point_t;

typedef struct
{
	float Kp;
	
	float Deadband;
	float MaxOutput;
	
	float Value;
	float Ref;
	float Output;
	
	Signal_TypeDef Signal;
}TrackValue_TypeDef;
*/

void absLimit(float* Val, float Limit);

float Min_f(float x, float y);
float Max_f(float x, float y);
float MinAbs_f(float x, float y);
float MaxAbs_f(float x, float y);

float InvSqrt(float Val);

uint8_t ValueInRange_u(uint32_t Value, uint32_t Min, uint32_t Max);
uint8_t ValueInRange_i(int32_t Value, int32_t Min, int32_t Max);
uint8_t ValueInRange_f(float Value, float Min, float Max);
float FlexibelValue(float dstVal, float srcVal, float step);

//double User_cos_f32(float Value);
//double User_sin_f32(float Value);
/*
//1®¨?°Í®Æ?
void TrackValue_Init(TrackValue_TypeDef *TrackValue, float Kp, float Deadband, float MaxOutput);
void TrackValue_Reset(TrackValue_TypeDef *TrackValue, float Kp);
void TrackValue_Calc(TrackValue_TypeDef *TrackValue);
*/
#endif
