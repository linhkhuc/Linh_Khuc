#include "pid.h"
#include "tim.h"
#include <stdio.h>

#define outMax						999
#define outMin						0

float Input, Output, Setpoint, error;
float errSum, deltaErr, dErr,  pre_err, pre_pre_err;
PIDStruct_t PIDStruct = {0, 0, 0};

uint32_t SampleTime = 1000;
uint32_t lastTime;
float PWM_Duty;

void PID_Controller(float Kp, float Ki, float Kd, float setpoint, uint32_t SampleTime)
{
	SetSampleTime(SampleTime);
	SetpointSet(setpoint);
	SetParameters(Kp, Ki, Kd);
	Compute();
	PWM_Duty = Output/(outMax + 1);
	TIM1->CCR3 = PWM_Duty;
}

void Compute(void)
{
	
	uint32_t now = HAL_GetTick();
	uint32_t timeChange = (now - lastTime);
	if (timeChange >= SampleTime)
	{
		error = Setpoint - Input;
		deltaErr = error - pre_err;
		errSum += error;
		dErr = (error - 2 * pre_err + pre_pre_err);
		
		Output += PIDStruct.Kp * deltaErr + PIDStruct.Ki * 0.5 * errSum + PIDStruct.Kd * dErr;
		if (Output > outMax) Output = outMax;
		else if (Output < outMin) Output = outMin;
		pre_pre_err = pre_err;
		pre_err = error;
		lastTime = now;
	}
}

void SetpointSet(float value)
{
	Setpoint = value;
}

void SetParameters(float Kp, float Ki, float Kd)
{
	if((Kp < 0) || (Ki < 0) || (Kd < 0))
	{
		return;
	}
	float SampleTimeInSec = ((float) SampleTime) / 1000;
	PIDStruct.Kp = Kp;
	PIDStruct.Ki = Ki * SampleTimeInSec;
	PIDStruct.Kd = Kd / SampleTimeInSec;
}

void SetSampleTime(uint32_t NewSampleTime)
{
	if (NewSampleTime > 0)
	{
		float ratio = ((float) NewSampleTime) / ((float) SampleTime);
		PIDStruct.Ki *= ratio;
		PIDStruct.Kd /= ratio;
		SampleTime = (uint32_t) NewSampleTime;
	}
}

