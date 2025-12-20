/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:03:10 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/19 14:20:57 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	valid_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
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

void	print_error(char **argv)
{
	if (ft_atoi(argv[1]) < 1)
	{
		write(2, "ERROR: Minimum 1 philosopher\n", 30);
		exit(EXIT_FAILURE);
	}
	write(2, "ERROR: Try: ./philo 5 20 5 5\n", 30);
	exit(EXIT_FAILURE);
}

void	init_check(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) < 1 || !valid_input(argv))
			print_error(argv);
		if (argc == 6)
		{
			if (ft_atoi(argv[5]) < 1)
			{
				printf("ERROR: Minimum 1 meal.\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		printf("Error: Philosophers need 4 arguments.\n");
		exit(EXIT_FAILURE);
	}
}
