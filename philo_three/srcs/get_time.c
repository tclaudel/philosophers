#include "../includes/philosophers.h"

clock_t				get_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((clock_t)tv.tv_sec * 1000 + (clock_t)tv.tv_usec / 1000);
}
