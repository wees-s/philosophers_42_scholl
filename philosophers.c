#include "philosophers.h"

void    threads_and_mutexes(t_node **nodes)
{
    t_node  *individual_node;
    t_node  *begin_list;
    int     index_mutex;

    begin_list = (*nodes);
    index_mutex = 0;
    individual_node = *nodes;
    while (individual_node)
    {
        if (individual_node->next == begin_list)
        {
            individual_node->left = &individual_node->mutex->hashi[index_mutex];
            individual_node->right = begin_list->left;
        }
        else
        {
            individual_node->left = &individual_node->mutex->hashi[index_mutex];
            individual_node->right = &individual_node->mutex->hashi[index_mutex + 1];
        }
        pthread_create(&individual_node->thread_id, NULL, routine, individual_node);
        individual_node = individual_node->next;
        if (individual_node == begin_list)
            break ;
        index_mutex++;
    }
}

void    init_philo(t_rules *rules, char **argv, t_node **nodes)
{
    int     philosopher_index;
    int     ph_nb;
    int     hashi_index;
    t_mutex *mutex;
    
    rules->start_time = 0;
    mutex = malloc(sizeof(t_mutex));
    mutex->hashi = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
    hashi_index = 0;
    philosopher_index = 1;
    rules->ph_quantity = ft_atoi(argv[1]);
    ph_nb = rules->ph_quantity;
    rules->time_to_die = ft_atoi(argv[2]);
    rules->time_to_eat = ft_atoi(argv[3]);
    rules->time_to_sleep = ft_atoi(argv[4]);
    (*nodes) = create_elem(philosopher_index, rules, mutex);
    pthread_mutex_init(&mutex->hashi[hashi_index], NULL);
    hashi_index++;
    philosopher_index++;
    while (philosopher_index <= ph_nb)
    {
        pthread_mutex_init(&mutex->hashi[hashi_index], NULL);
        append_item(nodes, philosopher_index, rules, mutex);
        hashi_index++;
        philosopher_index++;
    }
}