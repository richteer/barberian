#include <pthread.h>
#include "threads.h"

pthread_t * threads;

int threads_init(int number)
{
	int i;
	int ret;

	threads = malloc(1, sizeof(pthread_t)*numbers);

	for (i = 0; i < number; i++) {
		if (ret = pthread_create(threads + i, NULL, func, args)) break;
	}

	return ret;
}
