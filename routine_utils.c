#include "philosophers.h"

void take_hashis(t_node *ptr)
{
    if (ptr->number % 2 == 0)
    {
        pthread_mutex_lock(ptr->left);
        pthread_mutex_lock(&ptr->mutex->write_lock);
        printf(" %luMS ", get_time() - ptr->rules->real_time);
        printf("|🥢👈 FILÓSOFO %d PEGOU O HASHI A ESQUERDA\n", ptr->number);
        printf("|==================================================|\n");
        pthread_mutex_unlock(&ptr->mutex->write_lock);
        pthread_mutex_lock(ptr->right);
        pthread_mutex_lock(&ptr->mutex->write_lock);
        printf(" %luMS ", get_time() - ptr->rules->real_time);
        printf("|👉🥢 FILÓSOFO %d PEGOU O HASHI A DIREITA\n", ptr->number);
        printf("|==================================================|\n");
        pthread_mutex_unlock(&ptr->mutex->write_lock);
    }
    else
    {
        pthread_mutex_lock(ptr->right);
        pthread_mutex_lock(&ptr->mutex->write_lock);
        printf(" %luMS ", get_time() - ptr->rules->real_time);
        printf("|🥢👈 FILÓSOFO %d PEGOU O HASHI A DIREITA\n", ptr->number);
        printf("|==================================================|\n");
        pthread_mutex_unlock(&ptr->mutex->write_lock);
        pthread_mutex_lock(ptr->left);
        pthread_mutex_lock(&ptr->mutex->write_lock);
        printf(" %luMS ", get_time() - ptr->rules->real_time);
        printf("|👉🥢 FILÓSOFO %d PEGOU O HASHI A ESQUERDA\n", ptr->number);
        printf("|==================================================|\n");
        pthread_mutex_unlock(&ptr->mutex->write_lock);
    }
}

void put_hashis(t_node *ptr)
{
    pthread_mutex_unlock(ptr->left);
    pthread_mutex_unlock(ptr->right);
}

void eat(t_node *ptr)
{
    pthread_mutex_lock(&ptr->mutex->meal_lock);
    ptr->last_meal = get_time();
    pthread_mutex_unlock(&ptr->mutex->meal_lock);
    pthread_mutex_lock(&ptr->mutex->write_lock);
    printf(" %luMS ", get_time() - ptr->rules->real_time);
    printf("|🥢🍜 FILÓSOFO %d ESTÁ COMENDO\n", ptr->number);
    printf("|==================================================|\n");
    pthread_mutex_unlock(&ptr->mutex->write_lock);
    usleep(ptr->rules->time_to_eat * 1000);
    ptr->meals++;
}

void philosophers_sleep(t_node *ptr)
{
    pthread_mutex_lock(&ptr->mutex->write_lock);
    printf(" %luMS ", get_time() - ptr->rules->real_time);
    printf("|😴💤 FILÓSOFO %d ESTÁ DORMINDO\n", ptr->number);
    printf("|==================================================|\n");
    pthread_mutex_unlock(&ptr->mutex->write_lock);
    usleep(ptr->rules->time_to_sleep * 1000);
}

void think(t_node *ptr)
{
    pthread_mutex_lock(&ptr->mutex->write_lock);
    printf(" %luMS ", get_time() - ptr->rules->real_time);
    printf("|🤯💬 FILÓSOFO %d ESTÁ PENSANDO\n", ptr->number);
    printf("|==================================================|\n");
    pthread_mutex_unlock(&ptr->mutex->write_lock);
}