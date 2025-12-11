#include "philosophers.h"

void *routine(void *ptr)
{
    t_node  *node;
    long    start;

    node = (t_node *)ptr;
    while (1)
    {
       // pthread_mutex_lock(&philo->info->start_lock);
        start = node->rules->start_time;
        //pthread_mutex_unlock(&philo->info->start_lock);

        if (start != 0)
            break;
        usleep(50);
    }
    printf("=== ROTINA DO FILÓSOFO: %d ===\n", node->number);
    return (NULL);
}