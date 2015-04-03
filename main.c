#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "types.h"

static int parse_args(barb_t * barb, cust_t * cust, int argc, char ** argv)
{
	int i;

	// TODO: Set defaults

	for (i = 1; i < argc; i++) {
		switch(argv[i][1]) {
			case 't': barb->proctime  = atoi(argv[++i]); break;
			case 'b': barb->number    = atoi(argv[++i]); break;

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
	cust_t cust = {0};
	barb_t barb = {0};

	parse_args(&barb, &cust, argc, argv);

	shop_open(&barb, &cust);

	return 0;
}
