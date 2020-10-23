#include "../includes/philosophers.h"

void	ft_error(const char *str, char exit_status)
{
	static char	output[200] = "\033[0;31;5;110mError : ";

	ft_strlcat(output, str, 25 + ft_strlen(str));
	ft_strlcat(output, "\n\033[0m", ft_strlen(output) + 8);
	write(2, output, ft_strlen(output));
	if (exit_status)
		exit(exit_status);
}

int		enougth_time(t_philo *philo, int needed_time, int opt, int *forks_id)
{
	int 	remain_lifetime;


	remain_lifetime = philo->last_meal + g_rules.die - get_ms();
	needed_time /= 1000;
	if (remain_lifetime > needed_time)
		return (1);
	usleep(remain_lifetime * 1000);
	if (opt == 1)
	{
		pthread_mutex_unlock(g_forks[forks_id[0]].fork);
		g_forks[forks_id[0]].status = 1;
		pthread_mutex_unlock(g_forks[forks_id[1]].fork);
		g_forks[forks_id[1]].status = 1;
	}
	display_status(philo->id, DEAD);
	g_dead = 1;
	return (0);
}

void	free_all(void)
{
	size_t		i;

	i = 0;
	free(g_philos);
	while (i < g_rules.philo_nb)
	{
		free(g_forks[i].fork);
		i++;
	}
	free(g_forks);
}
