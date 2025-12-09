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

// //GEPETECOOOOOOOOOOOOOOOOOOOOOOOO


// void print_status(t_list *ph, const char *msg)
// {
//     pthread_mutex_lock(&ph->info->write_lock);
//     printf("filosofo: %d %s\n", ph->ph_nb, msg);
//     pthread_mutex_unlock(&ph->info->write_lock);
// }


// //GEPETECOOOOOOOOOOOO ^^^^^^^^^^^^^

void	print_status(t_list **philos)
{
	pthread_mutex_lock(&(*philos)->info->write_lock);
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
	pthread_mutex_unlock(&(*philos)->info->write_lock);
}


// //GEPETECOOOOOOOOOOOOOOOOOOOOOO

// void *routine(void *ptr)
// {
//     t_list *ph = (t_list *)ptr;

//     // pequeno desincronizador inicial para evitar contenda inicial brutal
//     if (ph->ph_nb % 2 != 0)
//         usleep(100);

//     while (1) // loop infinito — substitua por condição se precisar terminar
//     {
//         // pensar
//         // usleep(ph->info->to_sleep * 1000); // exemplo se quiser

//         if (ph->ph_nb % 2 == 0)
//         {
//             pthread_mutex_lock(ph->left);
//             print_status(ph, "pegou o HASHI da esquerda");

//             pthread_mutex_lock(ph->right);
//             print_status(ph, "pegou o HASHI da direita");

//             print_status(ph, "deveria comer agora");
//             usleep(ph->info->to_eat * 1000); // simula comer

//             pthread_mutex_unlock(ph->right);
//             print_status(ph, "soltou o HASHI da direita");

//             pthread_mutex_unlock(ph->left);
//             print_status(ph, "soltou o HASHI da esquerda");
//         }
//         else
//         {
//             // pequeno delay pra mishmash inicial
//             usleep(50);

//             pthread_mutex_lock(ph->right);
//             print_status(ph, "pegou o HASHI da direita");

//             pthread_mutex_lock(ph->left);
//             print_status(ph, "pegou o HASHI da esquerda");

//             print_status(ph, "deveria comer agora");
//             usleep(ph->info->to_eat * 1000);

//             pthread_mutex_unlock(ph->left);
//             print_status(ph, "soltou o HASHI da esquerda");

//             pthread_mutex_unlock(ph->right);
//             print_status(ph, "soltou o HASHI da direita");
//         }

//         // respirar pra evitar monopolização
//         usleep(500);
//     }
//     return NULL;
// }


// //GEPETECOOOOOOOO ^^^^^^^^


void    *routine(void *ptr)
{
	t_list **philos = (t_list **)ptr;
	int i = 0;
	//eu daria um lock aqui
	if ((*philos)->ph_nb % 2 == 0)
	{
		//printf("filosofo %d tentando pegar garfo esquerdo\n", (*philos)->ph_nb);
		pthread_mutex_lock((*philos)->left);
		pthread_mutex_lock((*philos)->right);
		print_status(philos);
		pthread_mutex_unlock((*philos)->right);
		pthread_mutex_unlock((*philos)->left);
	}
	else
	{
		//printf("filosofo %d tentando pegar garfo esquerdo\n", (*philos)->ph_nb);
		usleep(1000);
		pthread_mutex_lock((*philos)->right);
		pthread_mutex_lock((*philos)->left);
		print_status(philos);
		pthread_mutex_unlock((*philos)->left);
		pthread_mutex_unlock((*philos)->right);
	}
	i++;
	return (NULL);
}
