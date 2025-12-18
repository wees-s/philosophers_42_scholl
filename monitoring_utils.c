#include "philosophers.h"

void	philo_eat_print(t_node *ptr, t_node *temp)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS | ✅ TODOS OS FILÓSOFOS COMERAM\n",
		get_time() - ptr->rules->real_time);
	printf("|==================================================|\n");
	temp = ptr;
	while (i < ptr->rules->ph_quantity)
	{
		printf(" ✅ FILÓSOFO %d COMEU [%d] VEZES\n", temp->number, temp->meals);
		temp = temp->next;
		i++;
	}
	printf("|==================================================|\n");
}

static void	print_dead(t_node *ptr)
{
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %ldMS | FILOSOFO %d MORREU ☠️\n",
		get_time() - ptr->rules->real_time, ptr->number);
	pthread_mutex_unlock(&ptr->mutex->write_lock);
}

void	*monitor_looping(t_node *ptr, t_node *begin_list)
{
	while (ptr)
	{
		if (ptr->rules->max_meals > 0)
		{
			pthread_mutex_lock(&ptr->mutex->max_meal_lock);
			eat_monitor(ptr);
			pthread_mutex_unlock(&ptr->mutex->max_meal_lock);
			if (ptr->rules->dead)
				return (NULL);
		}
		pthread_mutex_lock(&ptr->mutex->meal_lock);
		if (get_time() - ptr->last_meal > ptr->rules->time_to_die)
		{
			pthread_mutex_unlock(&ptr->mutex->meal_lock);
			print_dead(ptr);
			ptr->rules->dead = 1;
			return (NULL);
		}
		pthread_mutex_unlock(&ptr->mutex->meal_lock);
		ptr = ptr->next;
		if (ptr == begin_list)
			break ;
	}
	return ((void *)1);
}
