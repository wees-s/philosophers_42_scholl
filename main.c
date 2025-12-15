#include "philosophers.h"
/*
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	join_all_threads(t_node **nodes)
{
	t_node	*start;
	t_node	*curr;

	start = (*nodes);
	curr = (*nodes);
	if (!curr)
		return ;
	while (1)
	{
		pthread_join(curr->thread_id, NULL);
		curr = curr->next;
		if (curr == start)
			break ;
	}
}

int main(int argc, char **argv)
{
    t_rules rules;
    t_node  *nodes;
    int     first;
    long    start;
    t_node  *temp;

    if (argc == 5 || argc == 6)
    {
        if (ft_atoi(argv[1]) < 1 || !valid_input(argv))
            print_error(argv);
    }
    else
    {
        printf("Error: Philosophers need 4 arguments.\n");
        exit(EXIT_FAILURE);
    }
    init_philo(&rules, argv, &nodes);
    threads_and_mutexes(&nodes); //THREADS E MUTEXES CRIADOS
    nodes->rules->start_time = get_time();
    temp = nodes;
    first = 1;
    start = nodes->rules->start_time;
    pthread_mutex_init(&nodes->mutex->meal_lock, NULL);
    pthread_mutex_init(&nodes->mutex->max_meal_lock, NULL);
    pthread_mutex_init(&nodes->mutex->time_lock, NULL);
    pthread_mutex_init(&nodes->mutex->write_lock, NULL);
    while (temp && (temp != nodes || first))
    {
        first = 0;
        pthread_mutex_lock(&temp->mutex->meal_lock);
        temp->last_meal = start;
        temp->meals = 0;
        pthread_mutex_unlock(&temp->mutex->meal_lock);
        temp = temp->next;
    }
    pthread_create(&nodes->rules->monitor, NULL, monitor, nodes); //MONITOR CRIADO == NULL
    pthread_join(nodes->rules->monitor, NULL);
    printf("teste");
    join_all_threads(&nodes);
    return (0);
}*/
#include "philosophers.h"

long get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void join_all_threads(t_node **nodes)
{
    t_node  *start;
    t_node  *curr;

    start = (*nodes);
    curr = (*nodes);
    if (!curr)
        return;
    
    while (1)
    {
        pthread_join(curr->thread_id, NULL);
        curr = curr->next;
        if (curr == start)
            break;
    }
}

void destroy_mutexes(t_node *nodes)
{
    int i;

    if (!nodes)
        return;
        
    pthread_mutex_destroy(&nodes->mutex->meal_lock);
    pthread_mutex_destroy(&nodes->mutex->max_meal_lock);
    pthread_mutex_destroy(&nodes->mutex->time_lock);
    pthread_mutex_destroy(&nodes->mutex->write_lock);
    
    i = 0;
    while (i < nodes->rules->ph_quantity)
    {
        pthread_mutex_destroy(&nodes->mutex->hashi[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_rules rules;
    t_node  *nodes;
    int     first;
    long    start;
    t_node  *temp;

    if (argc == 5 || argc == 6)
    {
        if (ft_atoi(argv[1]) < 1 || !valid_input(argv))
            print_error(argv);
    }
    else
    {
        printf("Error: Philosophers need 4 arguments.\n");
        exit(EXIT_FAILURE);
    }
    
    init_philo(&rules, argv, &nodes);
    
    // Inicializa mutexes
    pthread_mutex_init(&nodes->mutex->meal_lock, NULL);
    pthread_mutex_init(&nodes->mutex->max_meal_lock, NULL);
    pthread_mutex_init(&nodes->mutex->time_lock, NULL);
    pthread_mutex_init(&nodes->mutex->write_lock, NULL);
    
    // Inicializa last_meal e meals
    temp = nodes;
    first = 1;
    start = get_time();
    nodes->rules->start_time = start;
    nodes->rules->real_time = start;
    
    while (temp && (temp != nodes || first))
    {
        first = 0;
        pthread_mutex_lock(&temp->mutex->meal_lock);
        temp->last_meal = start;
        temp->meals = 0;
        pthread_mutex_unlock(&temp->mutex->meal_lock);
        temp = temp->next;
    }
    
    // Cria threads
    threads_and_mutexes(&nodes);
    
    // Cria e aguarda monitor
    pthread_create(&nodes->rules->monitor, NULL, monitor, nodes);
    pthread_join(nodes->rules->monitor, NULL);
    
    // Aguarda todas as threads terminarem
    join_all_threads(&nodes);
    
    // Cleanup
    destroy_mutexes(nodes);
    free_list(&nodes);
    
    return (0);
}