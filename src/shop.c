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
	printf("Customer %d is now getting his hair cut\n", num);
	sleep(cargs->proctime);
	sem_post(cargs->semaphore);
	printf("Customer %d is now sporting a fancy new look :D\n", num);

}

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
		pthread_create(&foo, NULL, (void*(*)(void*)) customer_do, &cargs);
		sleep(cust->delay);
	}

	printf("No more customers!\n");
	while(1);

	return 0;
}
