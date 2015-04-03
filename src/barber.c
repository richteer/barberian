#include "barber.h"
#include <semaphore.h>


struct {
	sem_t semaphore;
	thread_t threads;

	int number;
	int proctime;
} barbers;

struct {
	// TODO: care about the number maybe
	int number; // Number of customers total left. If negative, infinite
	int delay;
	int variance;
} customers;

int barber_init(int barbs, int proc)
{
	sem_init(&barbers.semaphore, 0, barbs);
	barbers.number = barbs;
	barbers.proctime = proc;

	return 0;
}

int barber_cut(int cust_delay, int cust_variance)
{
	threads_init();

	// TODO: This
}
