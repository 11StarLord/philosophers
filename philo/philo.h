/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:34:34 by djoao             #+#    #+#             */
/*   Updated: 2025/02/10 09:34:38 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define W		"\033[1;37m"
# define B		"\033[1;34m"

typedef struct s_simulations
{
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	g_print_mutex;
	pthread_t		*threads;
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				death;
	int				ac;
	char			**av;
}	t_simulations;

typedef struct s_philo
{
	struct timeval	time_born;
	t_simulations	*sim_data;
	int				id;
	int				fork_left;
	int				fork_right;
	int				numb_meal;
	int				time_last_meal;
	int				stamina;
}	t_philo;

char	*check_char(char c);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		execution_time(struct timeval start);

int		check_philo_number(int n_philo);
int		check_limits(char **argv);
int		check_digits(char *str);
int		check_args(int argc, char **argv);

int		philo_die(t_philo *philo);
void	philo_sleep(t_philo *philo, int time);
void	start_philo(t_philo *philo, t_simulations *simulations, int id);
void	start_forks(t_simulations *simulations);
void	start_simulations(t_simulations *simulations, int argc, char **argv);
void	philo_eat(t_philo *philo);
void	check_forks(t_philo *philo);
void	print_status(t_philo *philo, char c);

void	cordinate_start(t_philo *philo);
void	philo_case_one(t_philo *philo);
void	*philo_life(void *arg);
void	clean_resources(t_simulations *simulations, t_philo *philo);

#endif
