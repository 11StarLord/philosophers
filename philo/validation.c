/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:43:02 by djoao             #+#    #+#             */
/*   Updated: 2025/02/10 09:43:08 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_number(int n_philo)
{
	if (n_philo > 200)
	{
		printf(RED"Number of philosophers above of 200\n"RST);
		return (1);
	}
	if (n_philo <= 0)
	{
		printf(RED"Error\n"RST);
		return (1);
	}
	return (0);
}

int	check_limits(char **argv)
{
	int	n_philo;

	n_philo = ft_atoi(argv[1]);
	return (check_philo_number(n_philo));
}

int	check_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("./philo nbr_of_philo time_to_die time_to_eat time_to_sleep\n");
		return (1);
	}
	if (check_limits(argv))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!check_digits(argv[i]))
		{
			printf(RED"Error\n"RST);
			return (1);
		}
		i++;
	}
	return (0);
}
