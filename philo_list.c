#include "philo.h"

t_list	*list_last(t_list *begin_list)
{
	while (begin_list -> next != NULL)
	{
		begin_list = begin_list -> next;
	}
	return (begin_list);
}


t_list	*create_elem(int ph_nb, t_philo *info)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	if (ptr)
	{
		ptr->ph_nb = ph_nb;
		ptr->next = NULL;
        ptr->prev = NULL;
        ptr->info = info;
	}
	return (ptr);
}

int	list_size(t_list *begin_list)
{
	int			i;
	t_list		*index;

	index = begin_list;
	i = 0;
	while (index)
	{
		i++;
		index = index -> next;
	}
	return (i);
}

void	append_item(t_list **ptr, int ph_nb, t_philo *info)
{
	t_list	*last;
	t_list	*item;

	if (!ptr)
		return ;
	item = create_elem(ph_nb, info);
	if (!item)
		return ;
	if (!*ptr)
	{
		*ptr = item;
		return ;
	}
	last = list_last(*ptr);
	last->next = item;
	last->next->prev = last;
	(*ptr)->prev = last->next;
}
