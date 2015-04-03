#include <stdio.h>
#include <time.h>
#include "barber.h"

void barber_do(barb_t * args, cust_t * cust)
{
	fprintf(stderr, "Sup from barber\n");

	// TODO: Figure out how to make it schtop
	while (1) {

		if (cust->waiting)
			process_customer(&cust);
		}
		// TODO: Go to sleep
	}
}
