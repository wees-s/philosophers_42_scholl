/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:03:38 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/20 11:28:04 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_hashis(t_node *ptr)
{
	if (ptr->number % 2 == 0)
		return (take_left_hashi(ptr));
	else
		return (take_right_hashi(ptr));
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
	if (is_dead(ptr))
		return ;
	pthread_mutex_lock(&ptr->mutex->write_lock);
	if (!is_dead(ptr))
	{
		printf(" %lu ", get_time() - ptr->rules->real_time);
		printf("|🥢🍜 philosopher %d is eating\n", ptr->number);
		printf("|====================================================|\n");
	}
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	p_sleep(ptr, 1);
	pthread_mutex_lock(&ptr->mutex->meal_lock);
	ptr->meals++;
	pthread_mutex_unlock(&ptr->mutex->meal_lock);
}

void	philosophers_sleep(t_node *ptr)
{
	if (is_dead(ptr))
		return ;
	pthread_mutex_lock(&ptr->mutex->write_lock);
	if (!is_dead(ptr))
	{
		printf(" %lu ", get_time() - ptr->rules->real_time);
		printf("|😴💤 philosopher %d is sleeping\n", ptr->number);
		printf("|====================================================|\n");
	}
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	p_sleep(ptr, 2);
}

void	think(t_node *ptr)
{
	if (is_dead(ptr))
		return ;
	pthread_mutex_lock(&ptr->mutex->write_lock);
	if (!is_dead(ptr))
	{
		printf(" %lu ", get_time() - ptr->rules->real_time);
		printf("|🤯💬 philosopher %d is thinking\n", ptr->number);
		printf("|====================================================|\n");
	}
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	if (ptr->number % 2 != 0 && ptr->rules->ph_quantity % 2 != 0)
		usleep(1000);
}
