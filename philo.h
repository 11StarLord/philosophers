#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_params
{
	pthread_t	*threads;
	pthread_mutex_t	init_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	g_print_mutex;
	int	numb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	died;
	int	ac;
	char	**av;
}	t_params;

typedef struct	s_philo
{
	int	id;
	int	numb_meal;
	int	time_last_meal;
	int	stamina;
	t_params	*par;
	struct timeval	time_born;
}	t_philo;

int	ft_isdigit (int c);
int	ft_atoi(const char *nptr);
int	execution_time(struct timeval start);
void	philo_sleep(t_philo *philo, int time);


int check_philo_number(int numb_philo);
int check_limits(char **argv);
int check_digits(char *str);
int check_args(int argc, char **argv);

void    init_philo(t_philo *philo, t_params *params, int id);
void    start_forks_mutex(t_params *params);
void    init_params(t_params *params, int argc, char **argv);


#endif
