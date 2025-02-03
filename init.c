#include "philo.h"

void    init_philo(t_philo *philo, t_params *params, int id) //Inicializa as informações de cada filósofo
{
    philo->id = id; //Define o ID único do filósofo (de 1 até o número total de filósofos)
    philo->par = params; //Conecta o filósofo à estrutura global de parâmetros
    philo->stamina = params->time_die; //Define a resistência inicial do filósofo como o tempo permitido antes de morrer sem comer
    philo->time_last_meal = 0; //Inicializa o tempo desde a última refeição como 0
    if (params->ac == 6) //Verifica se há um argumento extra indicando o número de refeições máximas. Se sim, converte esse valor para inteiro e o atribui. Caso contrário, define como -1, indicando refeições ilimitadas.
        philo->numb_meal = ft_atoi(params->av[5]);
    else
        philo->numb_meal = -1; //Valor especial para refeições ilimitadas
}

void    start_forks_mutex(t_params *params) //Inicializa os mutexes para os garfos (representam os garfos compartilhados)
{
    int i;
    int numb_philo;

    i = 0;
    numb_philo = params->numb_philo;
    params->eat_mutex = malloc(sizeof(pthread_mutex_t) * numb_philo); //Aloca memória para um array de mutexes, onde cada mutex representa um garfo
    if (params->eat_mutex == NULL) //Caso a alocação falhe, exibe uma mensagem de erro e encerra o programa
    {
        write(2, "Error: Mutex allocation failed\n", 31);
        exit(EXIT_FAILURE);
    }
    while (i < numb_philo)
    {
        if (pthread_mutex_init(&params->eat_mutex[i], NULL) != 0) //Itera por todos os mutexes e os inicializa
        {
            write(2, "Error: Mutex initialization failed\n", 35); //Se algum mutex não puder ser inicializado, exibe uma mensagem de erro e encerra o programa
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void    init_params(t_params *params, int argc, char **argv) //Inicializa os parâmetros globais
{
    params->ac = argc; //Armazena os argumentos e o número de argumentos na estrutura global.
    params->av = argv;
    params->numb_philo = ft_atoi(argv[1]); //Converte os valores fornecidos na linha de comando para inteiros e os armazena na estrutura
    params->time_die = ft_atoi(argv[2]);
    params->time_eat = ft_atoi(argv[3]);
    params->time_sleep = ft_atoi(argv[4]);
    params->died = 0; //Define params->died como 0, indicando que nenhum filósofo morreu até agora
    if (pthread_mutex_init(&params->init_mutex, NULL) != 0 || //init_mutex: Garante que os filósofos iniciem ao mesmo tempo
        pthread_mutex_init(&params->dead_mutex, NULL) != 0 || //dead_mutex: Protege o acesso à variável compartilhada died
        pthread_mutex_init(&params->g_print_mutex, NULL) != 0) //Garante que as mensagens de status sejam impressas de maneira ordenada
    {
        write(2, "Error: Initializing mutex\n", 26); //Se a inicialização falhar, exibe uma mensagem de erro e encerra o programa
        return ; //Pensar em substituir por return ;
    }
    start_forks_mutex(params); //inicializa os mutexes dos garfos
}