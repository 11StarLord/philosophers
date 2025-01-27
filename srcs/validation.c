#include "philo.h"

int check_philo_number(int numb_philo) //Verifica se o número de filósofos é válido
{
    if (numb_philo > 200)
    {
        printf("Number of philosophers exceeds 200\n");
        return (1);
    }
    if (numb_philo <= 0)
    {
        printf("\033[0;41mError\033[0m\n");
        return (1);
    }
    return (0);
}

int check_limits(char **argv) //Verifica se o número de filósofos está dentro do limite
{
    int numb_philo;

    numb_philo = ft_atoi(argv[1]);
    return (check_philo_number(numb_philo));
}

int check_digits(char *str) //Válida se a string contém paenas dígitos
{
    int i;

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

int check_args(int argc, char **argv) //Função principal para verificar argumentos
{
    int i;

    if (argc != 5 && argc != 6)
    {
        printf("./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
        return (1);
    }
    if (check_limits(argv))
        return (1);
    i = 1;
    while (i < argc)
    {
        if (!check_digits(argv[i]))
        {
            printf("\033[0;41mError\033[0m\n");
            return (1);
        }
        i++;
    }
    return (0);
}