#include <stdio.h>

#include "driver.h"

int (*driverMap[DRIVER_MAP_SIZE])(unsigned char* payload);

/* Define our event-consuming method. Returns 0 on success, and 1 on
 * failure. */
int consume(int* out, struct Event* event)
{
	unsigned instruction;

	/* Check that the instruction itself is valid. */
	instruction = (unsigned)event->instruction;
	if (driverMap[instruction] == 0)
	{
		printf("Error: No callback registered for instruction ID '%u'.\n",
			   instruction);
		return 1;
	}

	/* Call the method and "return" the value. */
	*out = (*driverMap[instruction])(event->payload);

	/* NB: If you were doing the memory allocation trick I mentioned in the
     * comments in driver_demo.c, you would free that memory here. */
	return 0;
}

/* Registers a function into the map. */
void reg(unsigned key, int (*cb)(unsigned char*)){driverMap[key] = cb;}
