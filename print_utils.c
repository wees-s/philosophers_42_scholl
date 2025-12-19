/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:06:12 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/19 14:06:14 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_fork_right(t_node *ptr)
{
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS ", get_time() - ptr->rules->real_time);
	printf("|🥢👈 philosopher %d has taken a fork - right\n", ptr->number);
	printf("|====================================================|\n");
	pthread_mutex_unlock(&ptr->mutex->write_lock);
}

void	print_fork_left(t_node *ptr)
{
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS ", get_time() - ptr->rules->real_time);
	printf("|🥢👈 philosopher %d has taken a fork - right\n", ptr->number);
	printf("|====================================================|\n");
	pthread_mutex_unlock(&ptr->mutex->write_lock);
}
