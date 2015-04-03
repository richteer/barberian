#include "barber.h"
#include <semaphore.h>

static sem_t barbers;
static int customers;

int barber_init(int barbs, int cust)
{
	customers = cust;
	sem_init(&barbers, 0, barbs);

	return 0;
}

int barber_cut(int barb_time, int cust_delay, int cust_variance)
{
	// TODO: This
}
