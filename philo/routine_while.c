/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_while.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:15:21 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/19 14:16:27 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine_while(t_node *node)
{
	int	has_forks;

	while (!is_dead(node))
	{
		has_forks = 0;
		if (take_hashis(node))
			has_forks = 1;
		if (is_dead(node))
		{
			if (has_forks)
				put_hashis(node);
			break ;
		}
		eat(node);
		put_hashis(node);
		if (is_dead(node))
			break ;
		philosophers_sleep(node);
		if (is_dead(node))
			break ;
		think(node);
	}
}
