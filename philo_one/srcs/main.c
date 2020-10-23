#include "../includes/philosophers.h"

t_rules				g_rules;
t_philo				*g_philos;
t_fork				*g_forks;
pthread_mutex_t		g_write;
int 				g_dead;


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
	if (!(g_forks = malloc(sizeof(t_fork) * g_rules.philo_nb)))
		ft_error("malloc error", 1);
	i = 0;
	while (i < g_rules.philo_nb)
	{
		if (!(g_forks[i].fork = malloc(sizeof(pthread_mutex_t))) ||
				(pthread_mutex_init(g_forks[i].fork, NULL)))
			ft_error("problem while ininting pthread_mutex_t", 1);
		g_forks[i].status = 1;
		g_philos[i].meal_counter = 0;
		g_philos[i].id = i;
		g_philos[i].status = THINKING;
		g_philos[i].action = g_rules.start;
		g_philos[i].last_meal = g_rules.start;
		i++;
	}
	pthread_mutex_init(&g_write, NULL);
}

void		create_philo_threads(void)
{
	pthread_t		*philo_thread;
	size_t			i;

	if (!(philo_thread = malloc(sizeof(pthread_t) * g_rules.philo_nb)))
		ft_error("malloc error", 1);
	i = 0;
	while (i < g_rules.philo_nb)
	{
		if (pthread_create(&philo_thread[i], NULL, &life, &g_philos[i]))
			ft_error("could not create thread", 1);
		i++;
	}
	i = 0;
	while (i < g_rules.philo_nb)
		pthread_join(philo_thread[i++], NULL);
	free(philo_thread);
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
