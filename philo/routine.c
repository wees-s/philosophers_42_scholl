/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:03:32 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/20 11:29:19 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_monitor(t_node *ptr)
{
	t_node	*begin_list;
	t_node	*temp;

	begin_list = ptr;
	temp = ptr;
	while (temp)
	{
		pthread_mutex_lock(&temp->mutex->meal_lock);
		if (temp->meals < temp->rules->max_meals)
		{
			pthread_mutex_unlock(&temp->mutex->meal_lock);
			return ;
		}
		pthread_mutex_unlock(&temp->mutex->meal_lock);
		temp = temp->next;
		if (temp == begin_list)
			break ;
	}
	philo_eat_print(ptr, temp);
	pthread_mutex_lock(&ptr->mutex->dead);
	ptr->rules->dead = 1;
	pthread_mutex_unlock(&ptr->mutex->dead);
	return ;
}

void	*monitor(void *head)
{
	t_node	*ptr;
	t_node	*begin_list;

	ptr = (t_node *)head;
	begin_list = ptr;
	pthread_mutex_lock(&ptr->mutex->dead);
	ptr->rules->dead = 0;
	pthread_mutex_unlock(&ptr->mutex->dead);
	while (!is_dead(ptr))
	{
		ptr = begin_list;
		if (monitor_looping(ptr, begin_list) == NULL)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	one_philosopher(t_node *node)
{
	pthread_mutex_lock(node->left);
	pthread_mutex_lock(&node->mutex->write_lock);
	if (!node->rules->dead)
	{
		printf(" %lu |🥢 philosopher 1 has taken a fork\n",
			get_time() - node->rules->real_time);
	}
	pthread_mutex_unlock(&node->mutex->write_lock);
	usleep(node->rules->time_to_die * 1000);
	pthread_mutex_lock(&node->mutex->write_lock);
	if (!node->rules->dead)
	{
		printf(" %lu | philosopher 1 died ☠️\n",
			get_time() - node->rules->real_time);
	}
	pthread_mutex_unlock(&node->mutex->write_lock);
	pthread_mutex_unlock(node->left);
}

void	wait_start(t_node *node)
{
	long	start;

	while (1)
	{
		start = node->rules->start_time;
		if (start != 0)
			break ;
		usleep(50);
	}
}

void	*routine(void *ptr)
{
	t_node	*node;

	node = (t_node *)ptr;
	if (node->rules->ph_quantity == 1)
	{
		one_philosopher(node);
		return (NULL);
	}
	wait_start(node);
	routine_while(ptr);
	return (NULL);
}
