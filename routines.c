#include "philo.h"

void philo_eat(t_philo *philo)/* O filósofo come, actualiza seu último tempo de refeição e reduz o número de refeições restantes*/
{
    print_status(philo, 'e'); //Exibe a acção "is eating"
    philo_sleep(philo, philo->par->time_eat); //Simula o tempo comendo
    pthread_mutex_lock(&philo->par->dead_mutex); //Protege o acesso às variáveis compartilhadas
    philo->time_last_meal = execution_time(philo->time_born); //Actualiza o tempo da última refeição 
    if (philo->numb_meal > 0) //Decrementa o número de refeições restantes (se aplicavel)
        philo->numb_meal--;
    pthread_mutex_unlock(&philo->par->dead_mutex); //Libera o Mutex
}

void    check_forks(t_philo *philo) /* O filósofo pega os garfos, come e depois libera os garfos  */
{
    int left_fork;
    int right_fork;

    left_fork = (philo->id - 1 + philo->par->numb_philo) % philo->par->numb_philo;
    right_fork = philo->id % philo->par->numb_philo;
    if (philo_die(philo)) //Verifica se o filósofo já morreu
        return ;
    if (left_fork < right_fork) //Lógica para evitar deadlock ao pegar os garfos
    {
        pthread_mutex_lock(&philo->par->eat_mutex[left_fork]); 
        pthread_mutex_lock(&philo->par->eat_mutex[right_fork]);
    }
    else
    {
        pthread_mutex_lock(&philo->par->eat_mutex[right_fork]);
        pthread_mutex_lock(&philo->par->eat_mutex[left_fork]);
    }
    print_status(philo, 'f'); //Exibe "has taken a fork" para ambos os garfos
    print_status(philo, 'f');
    philo_eat(philo); //Filósofo come
    pthread_mutex_unlock(&philo->par->eat_mutex[left_fork]); // Libera os garfos
    pthread_mutex_unlock(&philo->par->eat_mutex[right_fork]);
    print_status(philo, 's'); //Exibe "is sleeping"
    philo_sleep(philo, philo->par->time_sleep); //Simula o tempo dormindo
    print_status(philo, 't'); // Exibe "is thinking"
}

int philo_die(t_philo *philo) /* Verifica se o filósofo morreu */
{
    pthread_mutex_lock(&philo->par->dead_mutex); //Protege o acesso às variáveis compartilhadas
    if (philo->par->died || philo->numb_meal == 0) //Verifica se a simulação já terminou ou se o filósofo não tem mais refeições
    {
        pthread_mutex_unlock(&philo->par->dead_mutex); //Libera o mutex
        return (1);  //Retorna 1 (verdadeiro) se o filósofo morreu ou a simulação terminou
    }
    if (philo->stamina < execution_time(philo->time_born) - philo->time_last_meal) //Verifica se o filósofo morreu de fome
    {
        print_status(philo, 'd'); //Imprime que o filósofo morreu
        philo->par->died = 1; //Define a flag de morte na estrutura de parâmetros
        pthread_mutex_unlock(&philo->par->dead_mutex); //Libera o mutex
        return (1); //Retorna 1 (verdadeiro) indicando a morte
    }
    pthread_mutex_unlock(&philo->par->dead_mutex);  //Libera o mutex
    return (0); //Retorna 0 (falso) se o filósofo está vivo
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

void    print_status(t_philo *philo, char c) /* Exibe o status do filósofo de forma sincronizada */
{
    int elapsed_time;
    char *str;

    elapsed_time = execution_time(philo->time_born); // Calcula o tempo decorrido desde o tempo de nascimento do filósofo
    str = check_char(c); // Recebe o caractere c e retorna a string de status correspondente
    pthread_mutex_lock(&philo->par->g_print_mutex); // Bloqueia o mutex g_print_mutex. Este mutex é crucial para a sincronização da saída.  Ele garante que apenas uma thread (um filósofo) possa imprimir sua mensagem de status por vez.
    if (!philo->par->died && philo->numb_meal != 0) // Verifica se a simulação ainda não terminou (ou seja, nenhum filósofo morreu de fome).
        printf("%d %d %s", elapsed_time, philo->id, str); // Se as duas condições acima forem verdadeiras, imprime o status do filósofo
    pthread_mutex_unlock(&philo->par->g_print_mutex); // Libera o mutex g_print_mutex.  Isso permite que outro filósofo imprima seu status.
}