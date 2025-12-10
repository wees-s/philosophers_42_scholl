/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:31:47 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/09 17:19:47 by wedos-sa         ###   ########.fr       */
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

void	print_status(t_list **philos, long actual_time)
{
	actual_time = get_time() - (*philos)->info->start_time;
	pthread_mutex_lock(&(*philos)->info->write_lock);
	printf("time: %lu -> Filosofo: %d pegou o HASHI da esquerda\n", actual_time, (*philos)->ph_nb);
	printf("time: %lu -> Filosofo: %d pegou o HASHI da direita\n", actual_time, (*philos)->ph_nb);
	printf("time: %lu -> Filosofo: %d deveria comer agora\n", actual_time, (*philos)->ph_nb);
    usleep(1000000);
	printf("time: %lu -> Filosofo: %d soltou o HASHI da esquerda\n", actual_time, (*philos)->ph_nb);
	printf("time: %lu -> Filosofo: %d soltou o HASHI da direita\n", actual_time, (*philos)->ph_nb);
	pthread_mutex_unlock(&(*philos)->info->write_lock);
}

void *routine(void *ptr)
{
    t_list *philo = (t_list *)ptr;
    int     i = 0;
    long    start;

    while (1)
    {
        pthread_mutex_lock(&philo->info->start_lock);
        start = philo->info->start_time;
        pthread_mutex_unlock(&philo->info->start_lock);

        if (start != 0)
            break;
        usleep(50);
    }
    while (1)
    {
        if (philo->ph_nb % 2 == 0)
        {
            pthread_mutex_lock(philo->left);
            pthread_mutex_lock(philo->right);
            print_status(&philo, start);   // se sua função espera **t_list **, você passa &philo
            pthread_mutex_unlock(philo->right);
            pthread_mutex_unlock(philo->left);

            pthread_mutex_lock(&philo->info->write_lock);
            printf("filosofo: %d está dormindo\n", philo->ph_nb);
            pthread_mutex_unlock(&philo->info->write_lock);
            //usleep(1000000);
        }
        else
        {
            usleep(10);
            pthread_mutex_lock(philo->right);
            pthread_mutex_lock(philo->left);
            print_status(&philo, start);
            pthread_mutex_unlock(philo->left);
            pthread_mutex_unlock(philo->right);

            pthread_mutex_lock(&philo->info->write_lock);
            printf("filosofo: %d está dormindo\n", philo->ph_nb);
            pthread_mutex_unlock(&philo->info->write_lock);
            //usleep(1000000);
        }
    }
    i++;
    return NULL;
}