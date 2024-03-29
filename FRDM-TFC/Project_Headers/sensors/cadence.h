/*
 *	sensors.h
 *
 *  Created: Nov 6, 2014
 *  Updated: Nov 23, 2014
 *  Author:  Connor Newton
 */

#ifndef HALL_SENSORS_H_
#define HALL_SENSORS_H_

#include "devices/MKL25Z4.h"
#include "config.h"

typedef struct {
  const TPM_MemMapPtr TPM; //pointer to TPM module struct
  const uint8_t channel;   //channel occupied by sensor
  uint16_t cnv;            //timer value at last capture used for calculating next period
  uint32_t overflows;      //number of times parent timer has overflowed during current period
  uint32_t period;         //most recent event period in ticks
  const uint8_t epr;       //events per revolution
  uint8_t  flag;           //flag to signal new period available
  struct {
	  uint32_t data[CADENCE_BUFFER_SIZE];
	  uint16_t pos;
  } buffer;
} CadenceSensor_s;

extern CadenceSensor_s CadenceSensors[4];

void CadenceSensors_Init();
void FTM2_IRQHandler();
void FTM0_IRQHandler();

#endif /* HALL_SENSORS_H_ */
