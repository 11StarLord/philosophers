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

void	philo_sleep(t_philo *philo, int time) //Faz a thread dormir por um tempo especificado, verificando periodicamente se o filósofo morreu
{
	struct timeval start; //Variável que armazenará o tempo inicial
	long elapsed_time; //Declara uma variavel do tipo long para armazenar o tempo decorrido

	gettimeofday(&start, NULL); //Obtem o tempo actual e armazena em start
	while (1) //Inicia um loop infinito
	{
		elapsed_time = execution_time(start); //Calcula o tempo decorrido desde o inicio até o momento actual
		if (elapsed_time >= time || philo_die(philo)) //Verifica se o tempo decorrido for maior ou igual ao tempo desejado || Se o filósofo ainda está vivo
			break ;
		usleep (100);
	}
}
