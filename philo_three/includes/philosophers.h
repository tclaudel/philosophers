//
// Created by tclaudel on 10/1/20.
//

#ifndef PHILOSOPHERS_PHILOSOPHERS_H
# define PHILOSOPHERS_PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

extern sem_t		 	*g_write;
extern char 			g_died;

typedef struct 			s_fork
{
	int					status;
	sem_t				*forks;
}						t_fork;

extern t_fork			g_forks;

typedef enum 			e_status
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	SATIATED,
}						t_status;

typedef struct 			s_rules
{
	unsigned short 		philo_nb;
	unsigned int		die;
	unsigned int 		eat;
	unsigned int		sleep;
	unsigned int 		meat_nb;
	int 				simu_begin;
	clock_t 			start;
}						t_rules;

extern t_rules			g_rules;

typedef struct 			s_philo
{
	int 				id;
	clock_t				action;
	clock_t 			last_meal;
	int 				meal_counter;
	t_status 			status;
}						t_philo;

extern t_philo 			*g_philos;

void					ft_error(const char *str, char exit_status);
void 					init(int ac, char **av);
clock_t 				get_ms(void);
void 					*life(void *ptr);
void 					free_all(void);
void 					display_status(const int i, t_status status);
int						enougth_time(t_philo *philo, int needed_time, int opt, int *forks_id);

// libft

size_t					ft_strlcat(char *dest, const char *src, size_t count);
size_t					ft_strlen(const char *s);
int						ft_isdigit(int c);
int						ft_atoi(const char *nptr);
char					*ft_itoa_ll_base(unsigned long n, char *base);

// life

int						take_forks(t_philo *philo, int *fork_id);
int 					eating(t_philo *philo);
int 					sleeping(t_philo *philo);
int 					thinking(t_philo *philo);

#endif //PHILOSOPHERS_PHILOSOPHERS_H
