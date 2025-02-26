/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:34:14 by djoao             #+#    #+#             */
/*   Updated: 2025/02/10 09:34:17 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cordinate_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_data->start_mutex);
	gettimeofday(&philo->time_born, NULL);
	pthread_mutex_unlock(&philo->sim_data->start_mutex);
	if (philo->id % 2 != 0)
		philo_sleep(philo, 10);
}

void	philo_case_one(t_philo *philo)
{
	gettimeofday(&philo->time_born, NULL);
	philo_sleep(philo, philo->sim_data->time_die);
	printf(Y"%d %d has taken a fork\n"RST, 0, philo->id);
	printf(RED"%d %d death\n"RST,
		execution_time(philo->time_born), philo->id);
}

void	*philo_life(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	if (philo.sim_data->n_philo == 1)
	{
		philo_case_one(&philo);
		return (NULL);
	}
	else
		cordinate_start(&philo);
	while (philo.numb_meal != 0)
	{
		if (philo_die(&philo))
			break ;
		check_forks(&philo);
		print_status(&philo, 's');
		if (philo_die(&philo))
			break ;
		philo_sleep(&philo, philo.sim_data->time_sleep);
		print_status(&philo, 't');
		if (philo_die(&philo))
			break ;
	}
	return (NULL);
}

void	clean_resources(t_simulations *simulations, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < simulations->n_philo)
		pthread_mutex_destroy(&simulations->forks[i++]);
	pthread_mutex_destroy(&simulations->start_mutex);
	pthread_mutex_destroy(&simulations->dead_mutex);
	pthread_mutex_destroy(&simulations->g_print_mutex);
	free(simulations->forks);
	free(philo);
	free(simulations->threads);
}

int	main(int argc, char **argv)
{
	t_simulations	simulations;
	t_philo			*philo;
	int				i;

	if (check_args(argc, argv))
		return (1);
	start_simulations(&simulations, argc, argv);
	simulations.threads = malloc(sizeof(pthread_t) * simulations.n_philo);
	philo = malloc(sizeof(t_philo) * simulations.n_philo);
	i = 0;
	while (i < simulations.n_philo)
	{
		start_philo(&philo[i], &simulations, i + 1);
		if (pthread_create(&simulations.threads[i], NULL,
				&philo_life, &philo[i]) != 0)
			return (printf(RED"Thread creation failed"RST), 1);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < simulations.n_philo)
		pthread_join(simulations.threads[i++], NULL);
	clean_resources(&simulations, philo);
	return (0);
}
