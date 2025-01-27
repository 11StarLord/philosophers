#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_int(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].data = data;
		i++;
	}
}

int	main(void)
{
	printf("Hello World\n");
	return (0);
}
