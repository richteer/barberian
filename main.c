#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

typedef struct {
	int cust_num;
	int cust_delay;
	int cust_variance;
	int barb_num;
	int barb_time;
} args_t;

static int parse_args(args_t * arg, int argc, char ** argv)
{
	int i;

	for (i = 1; i < argc; i++) {
		switch(argv[i][1]) {
			case 'c': arg->cust_num      = atoi(argv[++i]); break;
			case 'd': arg->cust_delay    = atoi(argv[++i]); break;
			case 'v': arg->cust_variance = atoi(argv[++i]); break;
			case 'b': arg->barb_num      = atoi(argv[++i]); break;
			case 't': arg->barb_time     = atoi(argv[++i]); break;

			default : fprintf(stderr, "Unrecognized flag %s\n", argv[i]); break;
		}
	}

	return 0;
}

int main(int argc, char ** argv)
{
	args_t args = {0};

	parse_args(&args, argc, argv);

	barber_init(args.barb_num, args.barb_time);

	barber_cut(args.cust_delay, arg.cust_variance);

	return 0;
}
