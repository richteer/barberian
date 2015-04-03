#include "barber.h"
#include <semaphore.h>

sem_t barbers;

int barber_init(int barbs)
{
	return sem_init(&barbers, 0, barbs);
}
