/* Collector.c
 * =====================================================
 * ARM_SysTick timer driven data collection service.
 * 
 * Written for use with TFTP for FRDM-TFC.
 * 
 * Author: Connor Newton
 *   Date: November 24, 2014
 * -----------------------------------------------------
 * Any data to be collected with Collector should be
 * shared via its modules' header file.
 *
 * Collector only facilitates the collection of data
 * at specified intervals from other modules - the
 * actual data handling is performed by the TFTP
 * attribute's endpoint function.
 */

#include "telemetry/Collector.h"

/* Import Tftp */
#include "telemetry/tftp/tftp.h"

/* Import timer */
#include "support/ARM_SysTick.h"
#include "config.h"
#define TICKER TFC_Ticker[COLLECTOR_TICKER]

/* Include headers to access shared data */
#include "sensors/camera/LineScanCamera.h"

/* Define CollectorItems */
CollectorItem items[] = {
	/* [0] = */ { /* data = */ &LineScanImage0, /* deref = */ 1, /* endpoint = */ &TFTP_LINESCAN0_ENDPOINT, /* frequency = */ 1, /* misc...*/ 0,0 }
};
#define NUM_ITEMS ( (sizeof items) / (sizeof (CollectorItem)) )

/* Collector initialization routine */
void Collector_Init()
{

	/* Initialize CollectorItems */
	for (uint32_t i = 0; i < NUM_ITEMS; i++ )
	{
		/* Calculate period in ticks; initialize counter */
		items[i].period = SYSTICK_FREQUENCY/items[i].frequency;
		items[i].counter = 0;
	}

	/* Initialize PIT1 */
	// SOMETHING SOMETHING REGISTERS
}

CollectorStatus* Collector()
{
	/* Endpoint error reporting */
	static int8_t errors[NUM_ITEMS];
	static CollectorStatus status = { COLLECTOR_ENDPOINT_OK, errors };
	
	status.flag = COLLECTOR_ENDPOINT_OK; // Reset errors flag

	/* Handle CollectorItems */
	for (uint32_t i = 0; i < NUM_ITEMS; i++)
	{
		/* Add number of ticks since last epoch to counter */
		items[i].counter += TICKER;

		/* If CollectorItem counter has reached 
		   or exceeded period in ticks */
		if (items[i].counter >= items[i].period)
		{
			/* Reset counter to zero */
			items[i].counter = 0;
			
			/* Get pointer to data - this step required because
			 * location of some information (i.e. linescan images
			 * changes during operation */
			void* ptr = items[i].data;
			uint8_t r = items[i].deref;
			while(r) {
				ptr = (void*)(*((int*) ptr)); // Get address behind pointer.
				r--; // Decrement distance to data.
			}

			/* Push data onto endpoint */
			errors[i] = (*(items[i].endpoint))(ptr);

			/* Set CollectorStatus error flag if appropriate */
			if (errors[i]) status.flag = COLLECTOR_ENDPOINT_ERROR;
		}
	}

	/* Reset ticker to zero */
	TICKER = 0;
	
	/* Finished; return pointer to endpoint results */
	return &status;
}