#include "philosophers.h"

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

void	free_list(t_node **begin_list)
{
	t_free	p;

	if (!begin_list || !*begin_list)
		return ;
	p.start = *begin_list;
	p.total_nodes = p.start->rules->ph_quantity;
	p.current = p.start->next;
	if (p.start->mutex)
	{
		if (p.start->mutex->hashi)
			free(p.start->mutex->hashi);
		free(p.start->mutex);
	}
	free(p.start);
	p.i = 1;
	while (p.i < p.total_nodes && p.current)
	{
		p.to_free = p.current;
		p.current = p.current->next;
		free(p.to_free);
		p.i++;
	}
	*begin_list = NULL;
}

void	take_right_hashi(t_node *ptr)
{
	pthread_mutex_lock(ptr->right);
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS ", get_time() - ptr->rules->real_time);
	printf("|🥢👈 FILÓSOFO %d PEGOU O HASHI A DIREITA\n", ptr->number);
	printf("|==================================================|\n");
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	pthread_mutex_lock(ptr->left);
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS ", get_time() - ptr->rules->real_time);
	printf("|👉🥢 FILÓSOFO %d PEGOU O HASHI A ESQUERDA\n", ptr->number);
	printf("|==================================================|\n");
	pthread_mutex_unlock(&ptr->mutex->write_lock);
}

void	take_left_hashi(t_node *ptr)
{
	pthread_mutex_lock(ptr->left);
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS ", get_time() - ptr->rules->real_time);
	printf("|🥢👈 FILÓSOFO %d PEGOU O HASHI A ESQUERDA\n", ptr->number);
	printf("|==================================================|\n");
	pthread_mutex_unlock(&ptr->mutex->write_lock);
	pthread_mutex_lock(ptr->right);
	pthread_mutex_lock(&ptr->mutex->write_lock);
	printf(" %luMS ", get_time() - ptr->rules->real_time);
	printf("|👉🥢 FILÓSOFO %d PEGOU O HASHI A DIREITA\n", ptr->number);
	printf("|==================================================|\n");
	pthread_mutex_unlock(&ptr->mutex->write_lock);
}
