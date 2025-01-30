#include "philo.h"

int	ft_isdigit (int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr != '\0' && ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result); 
}

int	execution_time(struct timeval start)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) -
			(start.tv_sec * 1000 + start.tv_usec / 1000));
}

void	philo_sleep(t_philo *philo, int time)
{
	struct timeval start;
	long elapsed_time;

	gettimeofday(&start, NULL);
	while (1)
	{
		elapsed_time = execution_time(start);
		if (elapsed_time >= time || philo_die(philo))
			break ;
		usleep (100);
	}
}
