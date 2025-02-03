#include "philo.h"

static void cordinate_start(t_philo *philo) //Aguarda a inicialização dos filósofos e sincroniza o tempo de início
{
	pthread_mutex_lock(&philo->par->init_mutex); //Tranca o mutex de inicialização
	gettimeofday(&philo->time_born, NULL); //Obtém o tempo atual e armazena em time_born
	pthread_mutex_unlock(&philo->par->init_mutex); //Destranca o mutex de inicialização
	if (philo->id % 2 == 0) //Se o ID do filósofo for par
		philo_sleep(philo, 10); //Espera 10 microssegundos
}

static void	philo_case_one(t_philo *philo) //Caso especial para um único filósofo: ele pega o garfo e morre
{
	gettimeofday(&philo->time_born, NULL); //Obtém o tempo atual e armazena em time_born
	philo_sleep(philo, philo->par->time_die); //Espera o tempo para morrer
	printf("%d %d has taken a fork\n", 0, philo->id); //Imprime que pegou um garfo
	printf("%d %d \033[0;31mdied\033[0m\n", execution_time(philo->time_born), philo->id); //Imprime que morreu
}

static void	*philo_life(void *arg) //Função executada por cada thread de filósofo
{
	t_philo	*philo;

	philo = (t_philo *)arg; //Converte o argumento void* para t_philo*
	if (philo->par->numb_philo == 1) //Caso haja apenas um filósofo
	{
		philo_case_one(philo); //Executa a função para um filósofo
		return (NULL);
	}
	cordinate_start(philo); //Espera a inicialização
	while (philo->numb_meal != 0) //Enquanto o número de refeições não for 0
	{
		if (philo_die(philo)) //Verifica se o filósofo morreu
			break ; //Sai do loop se morreu
		check_forks(philo); //Tenta pegar os garfos e comer
		print_status(philo, 's'); //Imprime que está dormindo
		philo_sleep(philo, philo->par->time_sleep); //Simula o tempo dormindo
		print_status(philo, 't'); //Imprime que está pensando
	}
	return (NULL);
}

static void clean_resources(t_params *params, t_philo *philo) //Libera recursos e destrói os mutexes
{
	int	i;

	i = 0;
	while (i < params->numb_philo)
		pthread_mutex_destroy(&params->eat_mutex[i++]); // Destrói os mutexes dos garfos
	pthread_mutex_destroy(&params->init_mutex); //Destrói o mutex de inicialização
	pthread_mutex_destroy(&params->dead_mutex); //Destrói o mutex de morte
	pthread_mutex_destroy(&params->g_print_mutex); //Destrói o mutex de impressão
	free(params->eat_mutex); //Libera a memória alocada para os mutexes dos garfos
	free(philo); //Libera a memória alocada para os filósofos
	free(params->threads); //Libera a memória alocada para o array de threads
}

int	main(int argc, char **argv) //Função principal do programa
{
	t_params	params;
	t_philo	*philo;
	int	i;

	if (check_args(argc, argv)) // Verifica os argumentos
		return (1); //Retorna 1 se houver erro nos argumentos
	init_params(&params, argc, argv); //Inicializa os parâmetros
	params.threads = malloc(sizeof(pthread_t) * params.numb_philo); //Aloca espaço para as threads
	philo = malloc(sizeof(t_philo) * params.numb_philo); //Aloca espaço para os filósofos
	if (!params.threads || !philo) //Verifica se a alocação falhou
		return (printf("\033[0;41mMemory allocation failed\033[0m\n"), 1);
	i = 0;
	while (i < params.numb_philo) //Cria as threads para cada filósofo
	{
		init_philo(&philo[i], &params, i + 1); //Inicializa os dados de cada filósofo
		if (pthread_create(&params.threads[i], NULL, &philo_life, &philo[i]) != 0) // Cria uma nova thread executando a função 'philo_life'
			return (printf("\033[0;41mThread creation failed\033[0m\n"), 1);
		usleep(50); //Pausa por 50 microssegundos (para escalonar a criação das threads)
		i++;
	}
	i = 0;
	while (i < params.numb_philo) //Loop para esperar que todas as threads terminem
		pthread_join(params.threads[i++], NULL); // Aguarda a thread 'i' terminar
	clean_resources(&params, philo); //Limpa os recursos (mutexes, etc.)
	return (0);
}
