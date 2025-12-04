#include "philo.h"

t_list *list_last(t_list *head)
{
    t_list *node;

    if (!head)
        return NULL;

    node = head;
    while (node->next != head && node->next != NULL)
	{
        node = node->next;
	}
    return node;
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
	last = list_last(*ptr); //penúltimo item
	last->next = item; //próximo item do penúltimo item é igual ao item novo
	last->next->prev = last; //o prev do último item é igual ao penúltimo.
	(*ptr)->prev = last->next;//o prev do primeiro item da lista é o último item.
	last->next->next = *ptr;//o próximo item do último item agora é o primeiro item.
}
