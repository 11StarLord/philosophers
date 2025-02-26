/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:45:44 by djoao             #+#    #+#             */
/*   Updated: 2025/02/10 09:45:47 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_philo *philo, t_simulations *simulations, int id)
{
	philo->id = id;
	philo->sim_data = simulations;
	philo->stamina = simulations->time_die;
	philo->time_last_meal = 0;
	philo->fork_left = (philo->id - 1 + philo->sim_data->n_philo)
		% philo->sim_data->n_philo;
	philo->fork_right = philo->id % philo->sim_data->n_philo;
	if (simulations->ac == 6)
		philo->numb_meal = ft_atoi(simulations->av[5]);
	else
		philo->numb_meal = -1;
}

void	start_forks(t_simulations *simulations)
{
	int	i;
	int	n_philo;

	i = 0;
	n_philo = simulations->n_philo;
	simulations->forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (simulations->forks == NULL)
	{
		write(2, "Error: Mutex allocation failed\n", 31);
		return ;
	}
	while (i < n_philo)
	{
		if (pthread_mutex_init(&simulations->forks[i], NULL) != 0)
		{
			write(2, "Error: Mutex initialization failed\n", 35);
			return ;
		}
		i++;
	}
}

void	start_simulations(t_simulations *simulations, int argc, char **argv)
{
	simulations->ac = argc;
	simulations->av = argv;
	simulations->n_philo = ft_atoi(argv[1]);
	simulations->time_die = ft_atoi(argv[2]);
	simulations->time_eat = ft_atoi(argv[3]);
	simulations->time_sleep = ft_atoi(argv[4]);
	simulations->death = 0;
	if (pthread_mutex_init(&simulations->start_mutex, NULL) != 0
		|| pthread_mutex_init(&simulations->dead_mutex, NULL) != 0
		|| pthread_mutex_init(&simulations->g_print_mutex, NULL) != 0)
	{
		write(2, "Error: Initializing mutex\n", 26);
		return ;
	}
	start_forks(simulations);
}
