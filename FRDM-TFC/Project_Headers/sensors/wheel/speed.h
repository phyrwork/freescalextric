#ifndef WHEEL_SPEED_SENSOR_H
#define WHEEL_SPEED_SENSOR_H

#include "sensors/cadence.h"

typedef struct {
	float value;
	CadenceSensor_s *sensor; //pointer to a cadence sensor
	float ratio; //period ratio of wheel:sensor (wheel:motor = 8:1??)
	uint32_t timeout; //timeout ref
} WheelSpeedSensor_s;

extern WheelSpeedSensor_s WheelSpeedSensors[4];

void InitWheelSpeedSensors();
void UpdateWheelSpeed(WheelSpeedSensor_s *wheel);

#endif
