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

// //GEPETECOOOOOOOOOOOOOOOOOO


// static void init_table(t_philo *info, t_list **philos)
// {
//     t_list *start = *philos;
//     t_list *curr = *philos;
//     int i = 0;
//     int n = info->philosophers;

//     // percorre e atribui left/right corretamente
//     while (1)
//     {
//         curr->left = &info->hashi[i];
//         curr->right = &info->hashi[(i + 1) % n];

//         // passe o nó atual (curr) — NÃO passe &philos
//         pthread_create(&curr->thread, NULL, routine, curr);

//         curr = curr->next;
//         i++;
//         if (curr == start)
//             break;
//     }
// }


// // GEPETECOOOOOOOOOO ^^^^^^^^^^^^^

static void init_table(t_philo *info, t_list **philos)
{
	t_list *reset_list;
	int		i;

	i = 0;
	reset_list = (*philos);
	pthread_mutex_init(&(*philos)->info->write_lock, NULL);
	while (*philos)
	{
		if((*philos)->next == reset_list)
		{
			(*philos)->left = &info->hashi[i];
			(*philos)->right = reset_list->left;
			usleep(1000);
			pthread_create(&(*philos)->thread, NULL, routine, philos);
			break ;
		}
		(*philos)->left = &info->hashi[i];
		(*philos)->right = &info->hashi[i + 1];
		usleep(1000);
		pthread_create(&(*philos)->thread, NULL, routine, philos);
		(*philos) = (*philos)->next;
		i++;
	}
	(*philos) = reset_list;
}

// //GPTECOOOOOOOOOOOOOOOOOOO
// static void init_philo(char **argv, t_philo *info, t_list **philos)
// {
//     int i;
//     int n;

//     n = ft_atoi(argv[1]);
//     info->philosophers = n;
//     info->to_die = ft_atoi(argv[2]);
//     info->to_eat = ft_atoi(argv[3]);
//     info->to_sleep = ft_atoi(argv[4]);

//     // inicializa mutex global para prints
//     pthread_mutex_init(&info->write_lock, NULL);

//     // aloca e inicializa os forks
//     info->hashi = malloc(sizeof(pthread_mutex_t) * n);
//     if (!info->hashi)
//         exit(EXIT_FAILURE);
//     i = 0;
//     while (i < n)
//     {
//         pthread_mutex_init(&info->hashi[i], NULL);
//         i++;
//     }

//     // cria a lista circular: cria o primeiro e depois append
//     *philos = create_elem(0, info);
//     (*philos)->eating = 0;
//     (*philos)->sleeping = 0;
//     (*philos)->thinking = 0;

//     i = 1;
//     while (i < n)
//     {
//         append_item(philos, i, info);
//         i++;
//     }
// }
// //GEPETECOOOOOOOOOOOOOOOO ^^^^^^^^^

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
	init_philo(argv, &info, &philos);
	init_table(&info, &philos);
	join_all_thread(&philos);
	return (0);
}

/*
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
		printf("join aconteceu aqui\n"); // apagar
		if (curr == start)
			break ;
	}
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
			pthread_create(&(*philos)->thread, NULL, routine, NULL);
			printf("FILÓSOFO %d\n", i); // apagar
			printf("THREAD: %ld\n", (*philos)->thread); // apagar
			printf("HASHI LEFT: %p\n", (*philos)->left); // apagar
			printf("HASHI RIGHT: %p\n\n", (*philos)->right); // apagar
			break ;
		}
		(*philos)->left = &info->hashi[i];
		(*philos)->right = &info->hashi[i + 1];
		pthread_create(&(*philos)->thread, NULL, routine, NULL);
		//pthread_join((*philos)->thread, NULL);
		printf("FILÓSOFO %d\n", i); // apagar
		printf("THREAD: %ld\n", (*philos)->thread); // apagar
		printf("HASHI LEFT: %p\n", (*philos)->left); // apagar
		printf("HASHI RIGHT: %p\n\n", (*philos)->right); // apagar
		(*philos) = (*philos)->next;
		i++;
	}
	(*philos) = reset_list;
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
	printf("mutex criado com sucesso\n"); // apagar
	(*philos)->eating = 0;
	(*philos)->sleeping = 0;
	(*philos)->thinking = 0;
	info->hashi = malloc(sizeof(pthread_mutex_t) * info->philosophers);
	pthread_mutex_init(&info->hashi[j], NULL);
	printf("filosofo adicionado com sucesso\n"); // apagar
	printf("FILÓSOFO 0\n\n"); //apagar
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&info->hashi[j], NULL);
		printf("mutex criado com sucesso\n"); // apagar
		append_item(philos, i, info);
		printf("filosofo adicionado com sucesso\n"); // apagar
		printf("FILÓSOFO %d\n\n", i); // apagar
		i++;
		j++;
	}
	printf("\n\n\n\n"); // apagar
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
	init_philo(argv, &info, &philos);
	join_all_thread(&philos);
	return (0);
}
*/