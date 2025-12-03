/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:49:00 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/03 19:43:23 by wedos-sa         ###   ########.fr       */
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
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	init_philo(int argc, char **argv, t_philo *ph, t_list **philos)
{
	int		i;
	(void)argc;
	i = 0;
	philos = (t_list **)malloc(sizeof(t_list) * ft_atoi(argv[1]));
	ph->philosophers = ft_atoi(argv[1]);
	ph->to_die = ft_atoi(argv[2]);
	ph->to_eat = ft_atoi(argv[3]);
	ph->to_sleep = ft_atoi(argv[4]);
	printf("cheguei aqui 1\n");
	while (i < argc)
	{
		printf("cheguei aqui com sucesso\n");
		append_item(philos, i, ph);
		printf("philo = %d\n", (*philos)->ph_nb);
		i++;
	}
	printf("cheguei aqui 2\n");
}

int	main(int argc, char **argv)
{
	t_philo ph;
	t_list	*philos;

	if (argc != 5 || !valid_input(argv))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	init_philo(argc, argv, &ph, &philos);
	printf("cheguei aqui 3\n");
	while(philos)
	{
		printf("philo = %d\n", philos->ph_nb);
		philos = philos->next;
	}
	return (0);
}
