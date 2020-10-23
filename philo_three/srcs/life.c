#include "../includes/philosophers.h"

void	*life(void *ptr)
{
	t_philo		*philo;

	philo = ptr;
	while (1)
	{
		if (g_rules.philo_nb == 1)
		{
			display_status(0, FORK);
			usleep(g_rules.die * 1000);
			display_status(0, DEAD);
			break;
		}
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
}
