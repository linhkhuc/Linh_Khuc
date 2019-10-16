#ifndef __PID_H_
#define __PID_H_

#include "stdint.h"

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
}PIDStruct_t;

void PID_Controller(float Kp, float Ki, float Kd, float setpoint, uint32_t SampleTime);
void Compute(void);
void SetpointSet(float setpoint);
void SetParameters(float Kp, float Ki, float Kd);
void SetSampleTime(uint32_t NewSampleTime);


#endif

