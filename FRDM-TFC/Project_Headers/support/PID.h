/*
 * PID.h
 *
 *  Created on: Dec 22, 2014
 *      Author: Connor
 */

#ifndef PID_H_
#define PID_H_

#include <stdint.h>

#define ANTI_WINDUP_NONE  0
#define ANTI_WINDUP_CLAMP 1

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float time;
	float value;
	float value_max;
	float value_min;
	float error;
	float integral;
	uint8_t antiwindup;
	float windup_max;
	float windup_min;
	uint8_t clamped;
} PID_s;

void UpdatePID(PID_s *PID, float ref, float actual);

#endif /* PID_H_ */
