#include "philosophers.h"

void    *monitor(void *head)
{
    t_node  *ptr;

    ptr = (t_node *)head;
    ptr->rules->dead = 0;
    while (!ptr->rules->dead)
    {
        while (ptr)
        {
            pthread_mutex_lock(&ptr->mutex->meal_lock);
            if (get_time() - ptr->last_meal > ptr->rules->time_to_die)
            {
                pthread_mutex_unlock(&ptr->mutex->meal_lock);

                pthread_mutex_lock(&ptr->mutex->write_lock);
                printf("%ldMS |☠️⚰️| FILOSOFO %d MORREU\n", get_time() - ptr->rules->real_time, ptr->number);
                pthread_mutex_unlock(&ptr->mutex->write_lock);

                ptr->rules->dead = 1;
                exit(EXIT_FAILURE);
            }
            pthread_mutex_unlock(&ptr->mutex->meal_lock);

            ptr = ptr->next;
        }
        usleep(500);
    }
    return (NULL);
}

void    *routine(void *ptr)
{
    t_node  *node;
    long    start;

    node = (t_node *)ptr;
    while (1)
    {
        start = node->rules->start_time;
        if (start != 0)
            break;
        usleep(50);
    }
    pthread_mutex_lock(&node->mutex->time_lock);
    node->rules->real_time = get_time();
    pthread_mutex_unlock(&node->mutex->time_lock);
    while (1)
    {
        take_hashis(ptr);
        eat(ptr);
        put_hashis(ptr);
        philosophers_sleep(ptr);
        think(ptr);
    }
    return (NULL);
}