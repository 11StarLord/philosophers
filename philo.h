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

typedef struct s_params
{
	pthread_mutex_t	init_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	g_print_mutex;
	pthread_t		*threads;
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				died;
	int				ac;
	char			**av;
}	t_params;

typedef struct s_philo
{
	struct timeval	time_born;
	t_params		*par;
	int				id;
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
void	init_philo(t_philo *philo, t_params *params, int id);
void	start_forks_mutex(t_params *params);
void	init_params(t_params *params, int argc, char **argv);
void	philo_eat(t_philo *philo);
void	check_forks(t_philo *philo);
void	print_status(t_philo *philo, char c);

void	cordinate_start(t_philo *philo);
void	philo_case_one(t_philo *philo);
void	*philo_life(void *arg);
void	clean_resources(t_params *params, t_philo *philo);

#endif
