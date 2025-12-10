/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:49:00 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/09 17:32:18 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while(argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				write(2, "Only DIGITS are accepted.\n", 27);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	join_all_thread(t_list **philos)
{
	t_list	*start;
	t_list	*curr;

	start = (*philos);
	curr = (*philos);
	if (!curr)
		return ;
	while (1)
	{
		pthread_join(curr->thread, NULL);
		curr = curr->next;
		if (curr == start)
			break ;
	}
}

static void init_table(t_philo *info, t_list **philos)
{
    t_list *reset_list;
    t_list *node;
    int     i;

    reset_list = *philos;
    node = *philos;
    i = 0;

    pthread_mutex_init(&info->write_lock, NULL);

    while (node)
    {
        // Set garfos
        if (node->next == reset_list)
        {
            node->left = &info->hashi[i];
            node->right = reset_list->left;
        }
        else
        {
            node->left = &info->hashi[i];
            node->right = &info->hashi[i + 1];
        }

        // Cria a thread passando o FILÓSOFO individual
        pthread_create(&node->thread, NULL, routine, node);

        node = node->next;
        if (node == reset_list)
            break;
        i++;
    }
}

static void	init_philo(char **argv, t_philo *info, t_list **philos)
{
	int		i;
	int		j;

	j = 0;
	i = 1;
	info->philosophers = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	(*philos) = create_elem(0, info);
	(*philos)->eating = 0;
	(*philos)->sleeping = 0;
	(*philos)->thinking = 0;
	info->hashi = malloc(sizeof(pthread_mutex_t) * info->philosophers);
	pthread_mutex_init(&info->hashi[j], NULL);
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&info->hashi[j], NULL);
		append_item(philos, i, info);
		i++;
		j++;
	}
	init_table(info, philos);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


int	main(int argc, char **argv)
{
	t_philo info;
	t_list	*philos;

	if (argc != 5 || !valid_input(argv) || ft_atoi(argv[1]) < 1)
	{
		if (ft_atoi(argv[1]) < 1)
		{
			write(2, "ERROR: Minimum 1 philosopher\n", 30);
			return (1);
		}
		write(2, "ERROR: Try: ./philo 5 20 5 5\n", 30);
		return (0);
	}
	pthread_mutex_lock(&info.start_lock);
	info.start_time = 0;
	pthread_mutex_unlock(&info.start_lock);
	philos = (t_list *)malloc(sizeof(t_list) * ft_atoi(argv[1]));
	init_philo(argv, &info, &philos);
	//init_table(&info, &philos);

	// Agora que TODAS as threads existem:
	pthread_mutex_lock(&info.start_lock);
	info.start_time = get_time(); // seu timestamp base
	pthread_mutex_unlock(&info.start_lock);

	join_all_thread(&philos);
	return (0);
}