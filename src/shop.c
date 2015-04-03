#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "types.h"
#include "barber.h"

static pthread_t * barbers;  // Threads for the barbers
static pthread_t   custflow; // Threads for adding in new customers

static int barbers_exist(barb_t * barb, cust_t * cust)
{
	int i;
	int ret;
	void  * args[] = {barb, cust};

	barbers = malloc(barb->number*sizeof(pthread_t));

	for (i = 0; i < barb->number; i++) {
		// TODO: Set proper args here
		if (ret = pthread_create(barbers + i, NULL, (void* (*)(void*)) barber_do, args)) break;
	}

	return ret;
}

static int customers_exist(cust_t * cust)
{
	return pthread_create(&custflow, NULL, NULL, NULL);
}

int shop_open(barb_t * barb, cust_t *cust)
{
	int ret;

	// Start the relevant threads
	if (ret = barbers_exist(barb, cust)) return ret;
	ret = customers_exist(cust);

	return ret;
}

int shop_close(barb_t * barb)
{
	int i;

	// Join on the customer thread first...
	pthread_join(custflow, NULL);

	// ...because the barber threads will join immediately if there are no customers left.
	for (i = 0; i < barb->number; i++) {
		pthread_join(barbers[i], NULL);
	}

	free(barbers);
}
