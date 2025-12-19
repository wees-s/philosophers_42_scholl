/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:03:18 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/19 11:03:19 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	t_u(t_node *nd, t_node *lst, pthread_mutex_t *hsh, int i_m)
{
	t_node			*node;
	t_node			*begin_list;
	int				index_mutex;
	pthread_mutex_t	*hashi;

	begin_list = lst;
	index_mutex = i_m;
	node = nd;
	hashi = hsh;
	if (node->next == begin_list)
	{
		node->left = &hashi[index_mutex];
		node->right = begin_list->left;
	}
	else
	{
		node->left = &hashi[index_mutex];
		node->right = &hashi[index_mutex + 1];
	}
	pthread_create(&node->thread_id, NULL, routine, node);
}

void	threads_and_mutexes(t_node **nodes)
{
	t_node			*node;
	t_node			*begin_list;
	int				index_mutex;
	pthread_mutex_t	*hashi;

	begin_list = (*nodes);
	index_mutex = 0;
	node = *nodes;
	hashi = node->mutex->hashi;
	while (node)
	{
		t_u(node, begin_list, hashi, index_mutex);
		node = node->next;
		if (node == begin_list)
			break ;
		index_mutex++;
	}
}

static void	init_rules(t_rules *rules, int flag, char **argv)
{
	if (flag == 1)
	{
		rules->start_time = 0;
		rules->dead = 0;
		return ;
	}
	else if (flag == 2)
	{
		rules->time_to_die = ft_atoi(argv[2]);
		rules->time_to_eat = ft_atoi(argv[3]);
		rules->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			rules->max_meals = ft_atoi(argv[5]);
		else
			rules->max_meals = -1;
		return ;
	}
}

static void	error_free(t_mutex	*mutex)
{
	free(mutex);
	exit(EXIT_FAILURE);
}

void	init_philo(t_rules *rules, char **argv, t_node **nodes)
{
	t_p	p;

	init_rules(rules, 1, argv);
	p.mutex = malloc(sizeof(t_mutex));
	if (!p.mutex)
		exit(EXIT_FAILURE);
	rules->ph_quantity = ft_atoi(argv[1]);
	p.mutex->hashi = malloc(sizeof(pthread_mutex_t) * rules->ph_quantity);
	if (!p.mutex->hashi)
		error_free(p.mutex);
	init_rules(rules, 2, argv);
	p.hashi_index = 0;
	while (p.hashi_index < rules->ph_quantity)
	{
		pthread_mutex_init(&p.mutex->hashi[p.hashi_index], NULL);
		p.hashi_index++;
	}
	p.philosopher_index = 1;
	(*nodes) = create_elem(p.philosopher_index, rules, p.mutex);
	p.philosopher_index++;
	while (p.philosopher_index <= rules->ph_quantity)
	{
		append_item(nodes, p.philosopher_index, rules, p.mutex);
		p.philosopher_index++;
	}
}
