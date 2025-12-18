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
	}
	else
	{
		printf("Error: Philosophers need 4 arguments.\n");
		exit(EXIT_FAILURE);
	}
}
