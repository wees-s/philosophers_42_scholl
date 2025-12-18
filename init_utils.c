#include "philosophers.h"

void	init_main(t_node *nodes)
{
	pthread_mutex_init(&nodes->mutex->meal_lock, NULL);
	pthread_mutex_init(&nodes->mutex->max_meal_lock, NULL);
	pthread_mutex_init(&nodes->mutex->time_lock, NULL);
	pthread_mutex_init(&nodes->mutex->write_lock, NULL);
	pthread_mutex_init(&nodes->mutex->dead, NULL);
}

void	init_timers(t_main *p)
{
	p->start = get_time();
	p->nodes->rules->start_time = p->start;
	p->nodes->rules->real_time = p->start;
	p->temp = p->nodes;
	p->first = 1;
	while (p->temp && (p->temp != p->nodes || p->first))
	{
		p->first = 0;
		pthread_mutex_lock(&p->temp->mutex->meal_lock);
		p->temp->last_meal = p->start;
		p->temp->meals = 0;
		pthread_mutex_unlock(&p->temp->mutex->meal_lock);
		p->temp = p->temp->next;
	}
}
