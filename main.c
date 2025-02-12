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
	pthread_mutex_lock(&philo->par->init_mutex);
	gettimeofday(&philo->time_born, NULL);
	pthread_mutex_unlock(&philo->par->init_mutex);
	if (philo->id % 2 == 0)
		philo_sleep(philo, 10);
}

void	philo_case_one(t_philo *philo)
{
	gettimeofday(&philo->time_born, NULL);
	philo_sleep(philo, philo->par->time_die);
	printf("%d %d has taken a fork\n", 0, philo->id);
	printf("%d %d \033[0;31mdied\033[0m\n",
		execution_time(philo->time_born), philo->id);
}

void	*philo_life(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	if (philo.par->n_philo == 1)
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
		philo_sleep(&philo, philo.par->time_sleep);
		print_status(&philo, 't');
		if (philo_die(&philo))
			break ;
	}
	return (NULL);
}

void	clean_resources(t_params *params, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < params->n_philo)
		pthread_mutex_destroy(&params->eat_mutex[i++]);
	pthread_mutex_destroy(&params->init_mutex);
	pthread_mutex_destroy(&params->dead_mutex);
	pthread_mutex_destroy(&params->g_print_mutex);
	free(params->eat_mutex);
	free(philo);
	free(params->threads);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		*philo;
	int			i;

	if (check_args(argc, argv))
		return (1);
	init_params(&params, argc, argv);
	params.threads = malloc(sizeof(pthread_t) * params.n_philo);
	philo = malloc(sizeof(t_philo) * params.n_philo);
	i = 0;
	while (i < params.n_philo)
	{
		init_philo(&philo[i], &params, i + 1);
		if (pthread_create(&params.threads[i], NULL,
				&philo_life, &philo[i]) != 0)
			return (printf("\033[0;41mThread creation failed\033[0m\n"), 1);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < params.n_philo)
		pthread_join(params.threads[i++], NULL);
	clean_resources(&params, philo);
	return (0);
}
