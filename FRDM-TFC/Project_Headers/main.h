/*
 * main.h
 *
 *  Created on: Feb 17, 2014
 *      Author: Matt
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "devices/MKL25Z4.h" /* include peripheral declarations */
#include "devices/arm_cm0.h"
#include "devices/CrystalClock.h"
#include "devices/TFC_SHIELD.h"
#include "devices/MMA8451Q.h"
#include "devices/HC05.h"
//#include "io/I2C.h"
#include "io/UART.h"
#include "io/DMA.h"
#include "io/ADC.h"
#include "sensors/vision/linescan.h"
#include "sensors/vision/exposure.h"
#include "sensors/vision/positioning.h"
#include "sensors/wheel/slip.h"
#include "sensors/motor/current.h"
#include "control/steering/Steering.h"
#include "control/motor/pwm.h"
#include "control/motor/torque.h"
#include "control/steering/Servo.h"
#include "control/TargetSpeed.h"
#include "control/differential.h"
#include "support/ARM_SysTick.h"
#include "support/carState_s.h"
#include "telemetry/Collector.h"
#include "support/Profiler.h"
#include "config.h"

uint32_t AnyTaskRequest();
uint32_t PollTaskRequest(uint32_t index);
void SetTaskRequest(uint32_t index);
void ClearTaskRequest(uint32_t index);
void TaskRequest_Init();
void UpdateTaskRequests();

void TFC_Init(carState_s* carState);
int main(void);
void evaluateMotorState(carState_s* carState);
void lineFollowingMode(carState_s* carState);


#endif /* MAIN_H_ */
