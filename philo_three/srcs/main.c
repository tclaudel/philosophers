#include "../includes/philosophers.h"

t_rules				g_rules;
t_philo				*g_philos;
t_fork 				g_forks;
sem_t 				*g_write;
char				g_died;

void		check_args(int ac, char **av)
{
	short	i;
	short	j;

	i = 0;
	if (ac != 5 && ac != 6)
		ft_error("Wrong number of arguments", 1);
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				ft_error("Arguments sould be numbers", 1);
	}
}

t_philo		*create_philo_and_forks(void)
{
	size_t		i;

	if (!(g_philos = malloc(sizeof(t_philo) * g_rules.philo_nb)))
		ft_error("malloc error", 1);
	i = 0;
	while (i < g_rules.philo_nb)
	{
		g_philos[i].meal_counter = 0;
		g_philos[i].id = i;
		g_philos[i].status = THINKING;
		g_philos[i].action = g_rules.start;
		g_philos[i].last_meal = g_rules.start;
		i++;
	}
	sem_unlink("/forks");
	if ((g_forks.forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, g_rules.philo_nb)) == SEM_FAILED)
		ft_error("sem_open failed", 1);
	g_forks.status = g_rules.philo_nb;
	sem_unlink("/write");
	if ((g_write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		ft_error("sem_open failed", 1);
}

void		create_philo_threads(void)
{
	pid_t 			pid[g_rules.philo_nb];
	int 			status;
	size_t			i;

	i = 0;
	while (i < g_rules.philo_nb)
	{
		if ((pid[i] = fork()) == -1)
			ft_error("fork failed", 1);
		if (pid[i] == 0) {
			life(&g_philos[i]);
			usleep(50);
		}
		i++;
	}
	while (1)
	{
		status = 0;
		i = -1;
		if (waitpid(-1, &status, 0) < 0)
		{
			i -= -1;
			while(++i, g_rules.philo_nb)
				kill(pid[i], SIGINT);
			break ;
		}
	}
	free_all();
}

void		init(int ac, char **av)
{
	g_rules.philo_nb = ft_atoi(av[1]);
	if (g_rules.philo_nb == 0)
		ft_error("philosophers must be at least 1", 1);
	g_rules.die = ft_atoi(av[2]);
	g_rules.eat = ft_atoi(av[3]) * 1000;
	g_rules.sleep = ft_atoi(av[4]) * 1000;
	g_rules.meat_nb = (ac == 6) ? ft_atoi(av[5]) : 0;
	g_rules.start = get_ms();
}

int			main(int ac, char **av)
{
	check_args(ac, av);
	init(ac, av);
	create_philo_and_forks();
	create_philo_threads();
}
