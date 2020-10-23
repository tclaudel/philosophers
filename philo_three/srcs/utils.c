#include "../includes/philosophers.h"

void				ft_error(const char *str, char exit_status)
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
		sem_post(g_forks.forks);
		sem_post(g_forks.forks);
		g_forks.status++;
		g_forks.status++;
	}
	display_status(philo->id, DEAD);
	g_died = 1;
	return (0);
}

void				free_all(void)
{
	free(g_philos);
	sem_unlink("/forks");
	sem_unlink("/write");
}
