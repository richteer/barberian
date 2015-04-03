#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "types.h"

static pthread_t * barbers;  // Threads for the barbers
static pthread_t * custflow; // Threads for adding in new customers

static int barbers_exist(barb_t * barb)
{
	int i;
	int ret;

	barbers = malloc(barb->number*sizeof(pthread_t));

	for (i = 0; i < barb->number; i++) {
		// TODO: Set proper args here
		if (ret = pthread_create(barbers + i, NULL, NULL, NULL)) break;
	}

	return ret;
}

static int customers_exist(cust_t * cust)
{
	// TODO: Spawn the customer thread
}

int shop_open(barb_t * barb, cust_t *cust)
{
	barbers_exist(barb);
	customers_exist(cust);
}

int shop_close(void)
{
	// Join on all the threads
}
