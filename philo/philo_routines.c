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
	philo_sleep(philo, philo->sim_data->time_eat);
	pthread_mutex_lock(&philo->sim_data->dead_mutex);
	philo->time_last_meal = execution_time(philo->time_born);
	if (philo->numb_meal > 0)
		philo->numb_meal--;
	pthread_mutex_unlock(&philo->sim_data->dead_mutex);
}

void	check_forks(t_philo *philo)
{
	if (philo_die(philo))
		return ;
	if (philo->fork_left < philo->fork_right)
	{
		pthread_mutex_lock(&philo->sim_data->forks[philo->fork_left]);
		pthread_mutex_lock(&philo->sim_data->forks[philo->fork_right]);
	}
	else
	{
		pthread_mutex_lock(&philo->sim_data->forks[philo->fork_right]);
		pthread_mutex_lock(&philo->sim_data->forks[philo->fork_left]);
	}
	print_status(philo, 'f');
	print_status(philo, 'f');
	philo_die(philo);
	philo_eat(philo);
	pthread_mutex_unlock(&philo->sim_data->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->sim_data->forks[philo->fork_right]);
	philo_die(philo);
}

int	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_data->dead_mutex);
	if (philo->sim_data->death == 1 || philo->numb_meal == 0)
	{
		pthread_mutex_unlock(&philo->sim_data->dead_mutex);
		return (1);
	}
	if (philo->stamina < execution_time(philo->time_born)
		- philo->time_last_meal)
	{
		print_status(philo, 'd');
		philo->sim_data->death = 1;
		pthread_mutex_unlock(&philo->sim_data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim_data->dead_mutex);
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
	pthread_mutex_lock(&philo->sim_data->g_print_mutex);
	if (!philo->sim_data->death && philo->numb_meal != 0)
		printf("%d %d %s", elapsed_time, philo->id, str);
	pthread_mutex_unlock(&philo->sim_data->g_print_mutex);
}
