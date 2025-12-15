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
	t_node	*to_free;

	if (!begin_list || !*begin_list)
		return ;
	free((*begin_list)->mutex->hashi);
	free((*begin_list)->mutex);
	while (*begin_list)
	{
		to_free = *begin_list;
		*begin_list = (*begin_list)->next;
		to_free->next = NULL;
		to_free->prev = NULL;

		free(to_free);
	}
	*begin_list = NULL;
}