/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:49:00 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/04 14:25:00 by wedos-sa         ###   ########.fr       */
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

static void	init_philo(int argc, char **argv, t_philo *ph, t_list **philos)
{
	int		i;
	(void)argc;
		
	i = 1;
	ph->philosophers = ft_atoi(argv[1]);
	ph->to_die = ft_atoi(argv[2]);
	ph->to_eat = ft_atoi(argv[3]);
	ph->to_sleep = ft_atoi(argv[4]);
	(*philos) = create_elem(0, ph);
	(*philos)->eating = 0;
	(*philos)->sleeping = 0;
	(*philos)->thinking = 0;
	//pthread_mutex_t	hashi;
	while (i < ft_atoi(argv[1]))
	{
		append_item(philos, i, ph);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo ph;
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
	init_philo(argc, argv, &ph, &philos);
	//printf("cheguei aqui 3\n");
	//printf("prev firts -> %d\n", philos->prev->ph_nb);
	while(philos)
	{
		printf("philo = %d\n", philos->ph_nb);
		printf("to die %d\nto_eat %d\nto_sleep %d\n\n", philos->info->to_die, philos->info->to_eat, philos->info->to_sleep);
		philos = philos->next;
	}
	return (0);
}
