/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:49:00 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/04 17:10:41 by wedos-sa         ###   ########.fr       */
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

static void init_table(t_philo *info, t_list **philos)
{
	t_list *reset_list;
	int		i;

	i = 0;
	reset_list = (*philos);
	while (*philos)
	{
		if((*philos)->next == reset_list)
		{
			(*philos)->left = &info->hashi[i];
			(*philos)->right = reset_list->left;
			printf("FILÓSOFO %d\n", i);
			printf("HASHI LEFT: %p\n", (*philos)->left);
			printf("HASHI RIGHT: %p\n\n", (*philos)->right);
			break ;
		}
		(*philos)->left = &info->hashi[i];
		(*philos)->right = &info->hashi[i + 1];
		printf("FILÓSOFO %d\n", i);
		printf("HASHI LEFT: %p\n", (*philos)->left);
		printf("HASHI RIGHT: %p\n\n", (*philos)->right);
		(*philos) = (*philos)->next;
		i++;
	}
}

static void	init_philo(int argc, char **argv, t_philo *info, t_list **philos)
{
	int		i;
	int		j;
	//pthread_mutex_t *hashi;
	(void)argc;

	j = 0;
	i = 1;
	info->philosophers = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	(*philos) = create_elem(0, info);
	printf("mutex criado com sucesso\n");
	(*philos)->eating = 0;
	(*philos)->sleeping = 0;
	(*philos)->thinking = 0;
	info->hashi = malloc(sizeof(pthread_mutex_t) * info->philosophers);
	pthread_mutex_init(&info->hashi[j], NULL);
	printf("filosofo adicionado com sucesso\n");
	printf("FILÓSOFO 0\n\n");
	//pthread_mutex_t	hashi;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&info->hashi[j], NULL);
		printf("mutex criado com sucesso\n");
		append_item(philos, i, info);
		printf("filosofo adicionado com sucesso\n");
		printf("FILÓSOFO %d\n\n", i);
		//pthread_mutex_init(&ph->hashi[j], NULL);
		//(*philos)->left = &ph->hashi[j];
		i++;
		j++;
	}
	printf("\n\n\n\n");
	init_table(info, philos);
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
	philos = (t_list *)malloc(sizeof(t_list) * ft_atoi(argv[1]));
	init_philo(argc, argv, &info, &philos);
	//printf("cheguei aqui 3\n");
	//printf("prev firts -> %d\n", philos->prev->ph_nb);
	// while(philos)
	// {
	// 	printf("philo = %d\n", philos->ph_nb);
	// 	printf("to die %d\nto_eat %d\nto_sleep %d\n\n", philos->info->to_die, philos->info->to_eat, philos->info->to_sleep);
	// 	philos = philos->next;
	// }
	return (0);
}
