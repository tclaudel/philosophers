#include "../includes/philosophers.h"

int		check_status(t_philo *philo)
{
	int remain_lifetime;

	if (g_dead != 0)
		return (1);
	remain_lifetime = philo->last_meal + g_rules.die - get_ms();
	if (remain_lifetime < 0)
	{
		display_status(philo->id, DEAD);
		g_dead = 1;
		return (1);
	}
	return (0);
}

int		take_forks(t_philo *philo, int *fork_id)
{
	while (g_forks[fork_id[0]].status == 0 &&
		g_forks[fork_id[1]].status == 0)
	{
		if (check_status(philo))
			return (0);
	}
	pthread_mutex_lock(g_forks[fork_id[0]].fork);
	pthread_mutex_lock(g_forks[fork_id[1]].fork);
	g_forks[fork_id[0]].status = 0;
	g_forks[fork_id[1]].status = 0;
	display_status(philo->id, FORK);
	display_status(philo->id, FORK);
	return (1);
}

int		eating(t_philo *philo)
{
	int		forks_id[2];

	if (check_status(philo))
		return (0);
	forks_id[0] = philo->id == 0 ? g_rules.philo_nb - 1 : philo->id - 1;
	forks_id[1] = philo->id;
	if (!take_forks(philo, forks_id))
		return (0);
	display_status(philo->id, EATING);
	philo->last_meal = get_ms();
	if (!enougth_time(philo, g_rules.sleep, 1, forks_id))
		return (0);
	usleep(g_rules.eat);
	philo->meal_counter++;
	pthread_mutex_unlock(g_forks[forks_id[0]].fork);
	pthread_mutex_unlock(g_forks[forks_id[1]].fork);
	g_forks[forks_id[0]].status = 1;
	g_forks[forks_id[1]].status = 1;
	if (philo->meal_counter == g_rules.meat_nb)
	{
		display_status(philo->id, SATIATED);
		return (0);
	}
	return (1);
}

int		sleeping(t_philo *philo)
{
	int 	*forks_id;

	if (check_status(philo))
		return (0);
	display_status(philo->id, SLEEPING);
	if (!enougth_time(philo, g_rules.sleep, 0, forks_id))
		return (0);
	usleep(g_rules.sleep);
	return (1);
}

int		thinking(t_philo *philo)
{
	if (check_status(philo))
		return (0);
	display_status(philo->id, THINKING);
	return (1);
}
