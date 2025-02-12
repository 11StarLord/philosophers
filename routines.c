/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:44:05 by djoao             #+#    #+#             */
/*   Updated: 2025/02/10 09:44:07 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	print_status(philo, 'e');
	philo_sleep(philo, philo->par->time_eat);
	pthread_mutex_lock(&philo->par->dead_mutex);
	philo->time_last_meal = execution_time(philo->time_born);
	if (philo->numb_meal > 0)
		philo->numb_meal--;
	pthread_mutex_unlock(&philo->par->dead_mutex);
}

void	check_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = (philo->id - 1 + philo->par->n_philo) % philo->par->n_philo;
	right_fork = philo->id % philo->par->n_philo;
	if (philo_die(philo))
		return ;
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&philo->par->eat_mutex[left_fork]);
		pthread_mutex_lock(&philo->par->eat_mutex[right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->par->eat_mutex[right_fork]);
		pthread_mutex_lock(&philo->par->eat_mutex[left_fork]);
	}
	print_status(philo, 'f');
	print_status(philo, 'f');
	philo_die(philo);
	philo_eat(philo);
	pthread_mutex_unlock(&philo->par->eat_mutex[left_fork]);
	pthread_mutex_unlock(&philo->par->eat_mutex[right_fork]);
	philo_die(philo);
}

int	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->par->dead_mutex);
	if (philo->par->died == 1 || philo->numb_meal == 0)
	{
		pthread_mutex_unlock(&philo->par->dead_mutex);
		return (1);
	}
	if (philo->stamina < execution_time(philo->time_born)
		- philo->time_last_meal)
	{
		print_status(philo, 'd');
		philo->par->died = 1;
		pthread_mutex_unlock(&philo->par->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->par->dead_mutex);
	return (0);
}

void	philo_sleep(t_philo *philo, int time)
{
	struct timeval		start;
	long				elapsed_time;

	gettimeofday(&start, NULL);
	while (1)
	{
		elapsed_time = execution_time(start);
		if (elapsed_time >= time || philo_die(philo))
			break ;
		usleep (100);
	}
}

void	print_status(t_philo *philo, char c)
{
	char	*str;
	int		elapsed_time;

	elapsed_time = execution_time(philo->time_born);
	str = check_char(c);
	pthread_mutex_lock(&philo->par->g_print_mutex);
	if (!philo->par->died && philo->numb_meal != 0)
		printf("%d %d %s", elapsed_time, philo->id, str);
	pthread_mutex_unlock(&philo->par->g_print_mutex);
}
