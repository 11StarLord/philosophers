#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_params
{
	pthread_t	*threads; //Array de threads dos filósofos
	pthread_mutex_t	init_mutex; //Mutex para sincronização inicial
	pthread_mutex_t	*eat_mutex; //Mutex para cada garfo
	pthread_mutex_t	dead_mutex; //Mutex para verificar morte
	pthread_mutex_t	g_print_mutex; //Mutex para impressão
	int	numb_philo; //Número de filósofos
	int	time_die; //Tempo para morrer
	int	time_eat; //Tempo para comer
	int	time_sleep; //Tempo para comer
	int	died; //Flag para indicar se algum filósofo morreu
	int	ac; //Contagem de argumentos
	char	**av; //valores dos argumentos
}	t_params;

typedef struct	s_philo
{
	int	id; //ID do filósofo
	int	numb_meal; //Número de refeições restantes (-1 para infinito)
	int	time_last_meal; //Tempo da última refeição
	int	stamina; //Tempo máximo antes de morrer
	t_params	*par; //Ponteiro para os parâmetros globais
	struct timeval	time_born; //Momento de nascimento do filósofo
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

void philo_eat(t_philo *philo);
void    check_forks(t_philo *philo);
int philo_die(t_philo *philo);
char    *check_char(char c);
void    print_status(t_philo *philo, char c);

#endif
