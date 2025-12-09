/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:31:47 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/09 14:41:18 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *string)
{
	int					i;
	int					sign;
	unsigned long int	nb;

	nb = 0;
	i = 0;
	sign = 1;
	while ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			sign = -1;
		else if (string[i] == '+')
			sign = 1;
		if (string[i++] < '0' && string[i] > '9')
			return (0);
	}
	while (string[i] >= '0' && string[i] <= '9')
	{
		nb = nb * 10 + (string[i] - 48);
		i++;
	}
	return (nb * sign);
}

void	print_status(t_list **philos)
{
	pthread_mutex_lock(&(*philos)->write_lock);
	printf("filosofo: %d pegou o HASHI da esquerda\n", (*philos)->ph_nb);
	// pthread_mutex_unlock(&(*philos)->write_lock);
	// pthread_mutex_lock(&(*philos)->write_lock);
	printf("filosofo: %d pegou o HASHI da direita\n", (*philos)->ph_nb);
	// pthread_mutex_unlock(&(*philos)->write_lock);
	// pthread_mutex_lock(&(*philos)->write_lock);
	printf("filosofo: %d deveria comer agora\n", (*philos)->ph_nb);
	// pthread_mutex_unlock(&(*philos)->write_lock);
	// pthread_mutex_lock(&(*philos)->write_lock);
	printf("filosofo: %d soltou o HASHI da esquerda\n", (*philos)->ph_nb);
	// pthread_mutex_unlock(&(*philos)->write_lock);
	// pthread_mutex_lock(&(*philos)->write_lock);
	printf("filosofo: %d soltou o HASHI da direita\n", (*philos)->ph_nb);
	pthread_mutex_unlock(&(*philos)->write_lock);
}

void    *routine(void *ptr)
{
	t_list **philos = (t_list **)ptr;
	//eu daria um lock aqui
	if ((*philos)->ph_nb % 2 == 0)
	{
		//printf("filosofo %d tentando pegar garfo esquerdo\n", (*philos)->ph_nb);
		pthread_mutex_lock((*philos)->left);
		pthread_mutex_lock((*philos)->right);
		print_status(philos);
		pthread_mutex_unlock((*philos)->left);
		pthread_mutex_unlock((*philos)->right);
	}
	else if((*philos)->ph_nb % 2 != 0)
	{
		usleep(10);
		//printf("filosofo %d tentando pegar garfo esquerdo\n", (*philos)->ph_nb);
		pthread_mutex_lock((*philos)->right);
		pthread_mutex_lock((*philos)->left);
		print_status(philos);
		pthread_mutex_unlock((*philos)->right);
		pthread_mutex_unlock((*philos)->left);
	}
	return (NULL);
}
