#include "philo.h"

void    init_philo(t_philo *philo, t_params *params, int id)
{
    philo->id = id;
    philo->par = params;
    philo->stamina = params->time_die;
    philo->time_last_meal = 0;
    if (params->ac == 6)
        philo->numb_meal = ft_atoi(params->av[5]);
    else
        philo->numb_meal = -1;
}

void    start_forks_mutex(t_params *params)
{
    int i;
    int numb_philo;

    i = 0;
    numb_philo = params->numb_philo;
    params->eat_mutex = malloc(sizeof(pthread_mutex_t) * numb_philo); 
    if (params->eat_mutex == NULL)
    {
        write(2, "Error: Mutex allocation failed\n", 31);
        exit(EXIT_FAILURE);
    }
    while (i < numb_philo)
    {
        if (pthread_mutex_init(&params->eat_mutex[i], NULL) != 0)
        {
            write(2, "Error: Mutex initialization failed\n", 35);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void    init_params(t_params *params, int argc, char **argv)
{
    params->ac = argc;
    params->av = argv;
    params->numb_philo = ft_atoi(argv[1]);
    params->time_die = ft_atoi(argv[2]);
    params->time_eat = ft_atoi(argv[3]);
    params->time_sleep = ft_atoi(argv[4]);
    params->died = 0;
    if (pthread_mutex_init(&params->init_mutex, NULL) != 0 ||
        pthread_mutex_init(&params->dead_mutex, NULL) != 0 ||
        phtread_mutex_init(&params->g_print_mutex, NULL) != 0)
    {
        write(2, "Error: Initializing mutex\n", 26);
        exit(EXIT_FAILURE);
    }
    start_forks_mutex(params);
}
