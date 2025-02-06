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

int	execution_time(struct timeval start) //Obtém o tempo decorrido em milissegundos desde um determinado tempo de referência 
{
	struct timeval now; //Variavel do tipo struct timeval que armazenará o tempo actual

	gettimeofday(&now, NULL); //Função que obtem o tempo actual e armazenará na estrutura now, NULL indica que não estamos interessados nas informações do fuso horário
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) -
			(start.tv_sec * 1000 + start.tv_usec / 1000)); //Calcula e retorna o tempo decorrido
			/*{ now.tv_sec * 1000} -> Converte os segundos actuais para milissegundos
			  { now.tv_usec / 1000} -> Converte os microssegundos atuais para milissegundos (divisão inteira, então a parte fracionária é descartada)
			  { start.tv_sec * 1000} -> Converte os segundos iniciais para milissegundos
			  { start.tv_usec / 1000} -> Converte os microssegundos iniciais para milissegundos
			*/
}

char    *check_char(char c) /* Retorna uma string com o status do filósofo */
{
    if (c == 'e')
        return ("\033[32mis eating\033[0m\n"); //Imprime verde is eating
    else if (c == 'f')
        return ("has taken a fork\n");
    else if (c == 's')
        return ("is sleeping\n");
    else if (c == 't')
        return ("is thinking\n");
    else
        return ("\033[0;31mdied\033[0m\n"); //Imprime vermelho died
}
