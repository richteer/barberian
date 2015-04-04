#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "types.h"

typedef struct {
	sem_t * semaphore;
	int proctime;
	int number;
} custarg_t;

static void customer_do(custarg_t * cargs)
{
	int num = cargs->number;

	printf("Customer %d is patiently waiting\n", num);

	sem_wait(cargs->semaphore);
	// Enter the critical section.
	//  A virtual barber is now processing this customer, only the number of
	//  barbers specified should be in the section at a time
	//   (In other words, the initial value for the semaphore)
	// NOTE: If no barbers are active, it should enter instantly.
	printf("Customer %d is now getting his hair cut\n", num);
	sleep(cargs->proctime); // Simulate the time it takes to get the haircut
	// Now leave the critical section, freeing the barber.
	sem_post(cargs->semaphore);

	printf("Customer %d is now sporting a fancy new look :D\n", num);
	// Thread is now done.
}

// Main operation logic
int shop_operate(barb_t * barb, cust_t * cust)
{
	pthread_t foo;
	custarg_t cargs;
	sem_t sem;
	int waiting;

	sem_init(&sem, 0, barb->number);
	cargs.semaphore = &sem;
	cargs.proctime = barb->proctime;

	srand(time(NULL));

	while (cust->number--) {
		printf("Customer %d arrives at the shop!\n", cust->number);
		// This is where I would check the maximum number of allowed waiting clients
		// But thanks to Linux's lovely decision, the value returned is 0, not
		// the number of waiting threads.
		/*
		sem_getvalue(&sem, &waiting);
		if (waiting == barb->maxwait) {
			printf("...but leaves when he sees how many people are waiting :(\n)");
			continue;
		}
		*/
		cargs.number = cust->number;
		// Start the customer thread.
		// NOTE: Thread references are not being persisted, as there isn't much of a point
		//  They should exit after acquiring the semaphore
		pthread_create(&foo, NULL, (void*(*)(void*)) customer_do, &cargs);

		// Wait for the next customer to arrive
		if (cust->variance)
			sleep(cust->delay + (rand() % (cust->variance*2 - cust->variance)));
		else
			sleep(cust->delay);

	}

	printf("No more customers!\n");

	// Spin forever, since the pthread references are thrown out and can't be joined.
	//  This is significant in case there still are threads that are waiting on a semaphore.
	while(1);

	return 0;
}
