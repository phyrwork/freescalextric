/*
 * SteeringControl.c
 *
 *  Created on: Nov 14, 2013
 *      Author: Matt
 */

#include "control/steering/Steering.h"
#include "support/Types.h"
#include "sensors/vision/positioning.h"
#include "support/ARM_SysTick.h"
#include <stdlib.h>

#define Kp 0.018f
#define Ki 0.02f//0.05f
#define Kd 0.0003f//0.0004f
#define INTEGRAL_LIMIT 1.0f
#define STEERING_LIMIT_UPPER 0.55f
#define STEERING_LIMIT_LOWER -0.45f
#define OFFSET -0.049//-0.062f

float getDesiredServoValue(int8_t position, int8_t setpoint)
{
	static float newPosition = 0;
	static float errorSum = 0;
	static float previousError = 0;
//	float Ki = TFC_ReadPot(1)*0.05f + 0.05f;
//	float Kd = TFC_ReadPot(1) * 0.0005f + 0.0005f;

	float error = (float) (setpoint - position);

	if (abs(newPosition) < STEERING_LIMIT_UPPER)
	{
		errorSum += error * (TFC_Ticker[1] / 10000.0f); //Normally then multiplied by dt, but ignored since we are assuming a constant iteration rate
	}

	if (errorSum > INTEGRAL_LIMIT)
	{
		errorSum = INTEGRAL_LIMIT;
	}
	else if (errorSum < -INTEGRAL_LIMIT)
	{
		errorSum = -INTEGRAL_LIMIT;
	}

	float errorDifferential = (error - previousError) / (TFC_Ticker[1] / 10000.0f); //Normally then divided by dt, but ignored since we are assuming a constant iteration rate
	TFC_Ticker[1] = 0;

	newPosition = (Kp * error) + (Ki * errorSum) + (Kd * errorDifferential);

	if (newPosition > STEERING_LIMIT_UPPER)
	{
		newPosition = STEERING_LIMIT_UPPER;
	}
	else if (newPosition < STEERING_LIMIT_LOWER)
	{
		newPosition = STEERING_LIMIT_LOWER;
	}
	previousError = error;

	return -(newPosition - OFFSET);
}
