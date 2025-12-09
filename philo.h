/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:50:26 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/12/09 14:03:35 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

int		ft_atoi(const char *string);

typedef struct	s_philo
{
	int				philosophers;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	pthread_mutex_t	*hashi;
}	t_philo;

typedef struct	s_list
{
	pthread_t		thread;
	struct s_list	*next;
	struct s_list	*prev;
	int				ph_nb;
	t_philo			*info;
	int				eating;
	int				sleeping;
	int				thinking;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t write_lock; //trava para printagem
	
} t_list;

void	append_item(t_list **ptr, int ph_nb, t_philo *info);
t_list	*create_elem(int ph_nb, t_philo *info);
t_list	*list_last(t_list *begin_list);
void    *routine(void *arg);

#endif
