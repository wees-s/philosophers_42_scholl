#include "philosophers.h"

void	take_hashis(t_node *ptr)
{
	if (ptr->number % 2 == 0)
		take_left_hashi(ptr);
	else
		take_right_hashi(ptr);
}

void	put_hashis(t_node *ptr)
{
	pthread_mutex_unlock(ptr->left);
	pthread_mutex_unlock(ptr->right);
}

void	eat(t_node *ptr)
{
	pthread_mutex_lock(&ptr->mutex->meal_lock);
	ptr->last_meal = get_time();
	pthread_mutex_unlock(&ptr->mutex->meal_lock);
	pthread_mutex_lock(&ptr->mutex->write_lock);
	if (!ptr->rules->dead)
	{
		printf(" %luMS ", get_time() - ptr->rules->real_time);
		printf("|🥢🍜 FILÓSOFO %d ESTÁ COMENDO\n", ptr->number);
		printf("|==================================================|\n");
	}
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	p_sleep(ptr, 1);
	ptr->meals++;
}

void	philosophers_sleep(t_node *ptr)
{
	pthread_mutex_lock(&ptr->mutex->write_lock);
	if (!ptr->rules->dead)
	{
		printf(" %luMS ", get_time() - ptr->rules->real_time);
		printf("|😴💤 FILÓSOFO %d ESTÁ DORMINDO\n", ptr->number);
		printf("|==================================================|\n");
	}
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	p_sleep(ptr, 2);
}

void	think(t_node *ptr)
{
	pthread_mutex_lock(&ptr->mutex->write_lock);
	if (!ptr->rules->dead)
	{
		printf(" %luMS ", get_time() - ptr->rules->real_time);
		printf("|🤯💬 FILÓSOFO %d ESTÁ PENSANDO\n", ptr->number);
		printf("|==================================================|\n");
	}
	pthread_mutex_unlock(&ptr->mutex->write_lock);
}
