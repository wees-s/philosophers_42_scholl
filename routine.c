#include "philosophers.h"
/*
static void    eat_monitor(t_node *ptr)
{
    t_node  *begin_list;
    int     i;

    i = 0;
    begin_list = ptr;
    while (ptr)
    {
        if (ptr->meals < ptr->rules->max_meals)
            return ;
        if (ptr->next == begin_list)
            break ;
        ptr = ptr->next;
    }
    pthread_mutex_lock(&ptr->mutex->write_lock);
    printf(" %luMS | ✅ TODOS OS FILÓSOFOS COMERAM\n", get_time() - ptr->rules->real_time);
    printf("|==================================================|\n");
    while (i < ptr->rules->ph_quantity)
    {
        printf(" ✅ FILÓSOFO %d COMEU [%d] VEZES\n", ptr->number, ptr->meals);
        ptr = ptr->next;
        i++;
    }
    printf("|==================================================|\n");
    pthread_mutex_destroy(&ptr->mutex->write_lock);
    //free_list(&ptr);
    exit(EXIT_SUCCESS);
}

void    *monitor(void *head)
{
    t_node  *ptr;

    ptr = (t_node *)head;
    ptr->rules->dead = 0;
    while (!ptr->rules->dead)
    {
        while (ptr)
        {
            pthread_mutex_lock(&ptr->mutex->max_meal_lock);
            eat_monitor(ptr);
            pthread_mutex_unlock(&ptr->mutex->max_meal_lock);
            pthread_mutex_lock(&ptr->mutex->meal_lock);
            if (get_time() - ptr->last_meal > ptr->rules->time_to_die)
            {
                pthread_mutex_unlock(&ptr->mutex->meal_lock);
                pthread_mutex_lock(&ptr->mutex->write_lock);
                printf(" %ldMS | FILOSOFO %d MORREU ☠️\n", get_time() - ptr->rules->real_time, ptr->number);
                pthread_mutex_destroy(&ptr->mutex->write_lock);
                ptr->rules->dead = 1;
                free_list(&ptr);
                //return(NULL);
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
    if (node->rules->ph_quantity == 1)
    {
        printf("teste\n");
        exit(EXIT_SUCCESS);
    }
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
*/
#include "philosophers.h"

static void eat_monitor(t_node *ptr)
{
    t_node  *begin_list;
    t_node  *temp;
    int     i;

    i = 0;
    begin_list = ptr;
    temp = ptr;
    
    // Verifica se todos comeram o suficiente
    while (temp)
    {
        pthread_mutex_lock(&temp->mutex->meal_lock);
        if (temp->meals < temp->rules->max_meals)
        {
            pthread_mutex_unlock(&temp->mutex->meal_lock);
            return;
        }
        pthread_mutex_unlock(&temp->mutex->meal_lock);
        
        temp = temp->next;
        if (temp == begin_list)
            break;
    }
    
    // Todos comeram - sinalizar fim
    pthread_mutex_lock(&ptr->mutex->write_lock);
    printf(" %luMS | ✅ TODOS OS FILÓSOFOS COMERAM\n", get_time() - ptr->rules->real_time);
    printf("|==================================================|\n");
    
    temp = ptr;
    while (i < ptr->rules->ph_quantity)
    {
        printf(" ✅ FILÓSOFO %d COMEU [%d] VEZES\n", temp->number, temp->meals);
        temp = temp->next;
        i++;
    }
    printf("|==================================================|\n");
    pthread_mutex_unlock(&ptr->mutex->write_lock);
    
    ptr->rules->dead = 1;
}

void *monitor(void *head)
{
    t_node  *ptr;
    t_node  *begin_list;

    ptr = (t_node *)head;
    begin_list = ptr;
    ptr->rules->dead = 0;
    
    while (!ptr->rules->dead)
    {
        ptr = begin_list;
        
        while (ptr)
        {
            // Verifica se tem max_meals definido
            if (ptr->rules->max_meals > 0)
            {
                pthread_mutex_lock(&ptr->mutex->max_meal_lock);
                eat_monitor(ptr);
                pthread_mutex_unlock(&ptr->mutex->max_meal_lock);
                
                if (ptr->rules->dead)
                    return (NULL);
            }
            
            // Verifica morte
            pthread_mutex_lock(&ptr->mutex->meal_lock);
            if (get_time() - ptr->last_meal > ptr->rules->time_to_die)
            {
                pthread_mutex_unlock(&ptr->mutex->meal_lock);
                pthread_mutex_lock(&ptr->mutex->write_lock);
                printf(" %ldMS | FILOSOFO %d MORREU ☠️\n", 
                       get_time() - ptr->rules->real_time, ptr->number);
                pthread_mutex_unlock(&ptr->mutex->write_lock);
                ptr->rules->dead = 1;
                return (NULL);
            }
            pthread_mutex_unlock(&ptr->mutex->meal_lock);
            
            ptr = ptr->next;
            if (ptr == begin_list)
                break;
        }
        
        usleep(1000);
    }
    return (NULL);
}

void *routine(void *ptr)
{
    t_node  *node;
    long    start;

    node = (t_node *)ptr;
    
    // Caso especial: 1 filósofo
    if (node->rules->ph_quantity == 1)
    {
        pthread_mutex_lock(node->left);
        pthread_mutex_lock(&node->mutex->write_lock);
        printf(" %luMS |🥢 FILÓSOFO 1 PEGOU UM HASHI\n", 
               get_time() - node->rules->real_time);
        pthread_mutex_unlock(&node->mutex->write_lock);
        usleep(node->rules->time_to_die * 1000);
        pthread_mutex_lock(&node->mutex->write_lock);
        printf(" %luMS | FILOSOFO 1 MORREU ☠️\n", 
               get_time() - node->rules->real_time);
        pthread_mutex_unlock(&node->mutex->write_lock);
        pthread_mutex_unlock(node->left);
        return (NULL);
    }
    
    // Espera start_time ser definido
    while (1)
    {
        start = node->rules->start_time;
        if (start != 0)
            break;
        usleep(50);
    }
    
    // Adiciona delay para filósofos ímpares evitar deadlock
    if (node->number % 2 != 0)
        usleep(1000);
    
    // Loop principal
    while (!node->rules->dead)
    {
        take_hashis(node);
        eat(node);
        put_hashis(node);
        
        if (node->rules->dead)
            break;
            
        philosophers_sleep(node);
        
        if (node->rules->dead)
            break;
            
        think(node);
    }
    return (NULL);
}