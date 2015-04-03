#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "types.h"

static int parse_args(barb_t * barb, cust_t * cust, int argc, char ** argv)
{
	int i;

	barb->proctime = 1;
	barb->number   = 3;
	barb->maxwait  = 5;

	cust->number   = 10;
	cust->delay    = 1;
	cust->variance = 0;

	for (i = 1; i < argc; i++) {
		switch(argv[i][1]) {
			case 't': barb->proctime  = atoi(argv[++i]); break;
			case 'b': barb->number    = atoi(argv[++i]); break;
			case 'w': barb->maxwait   = atoi(argv[++i]); break;

			case 'c': cust->number    = atoi(argv[++i]); break;
			case 'd': cust->delay     = atoi(argv[++i]); break;
			case 'v': cust->variance  = atoi(argv[++i]); break;

			default : fprintf(stderr, "Unrecognized flag %s\n", argv[i]); break;
		}
	}

	return 0;
}

int main(int argc, char ** argv)
{
	int ret;
	cust_t cust = {0};
	barb_t barb = {0};

	parse_args(&barb, &cust, argc, argv);

	printf("Starting day with %d barbers, taking %d seconds each.\n", barb.number, barb.proctime);
	if (cust.number < 0) {
		printf("Today the barbers will never see the end of customers arriving every %d seconds, with a variance of %d\n",
			cust.delay, cust.variance);
	}
	else {
		printf("There will be %d customers today, coming in every %d seconds with a variance of %d.\n",
			cust.number, cust.delay, cust.variance);
	}

	shop_operate(&barb, &cust);

	return 0;
}
