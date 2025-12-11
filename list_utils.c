#include "philosophers.h"

t_node	*create_elem(int philosopher_number, t_rules *rules, t_mutex *mutex)
{
	t_node	*ptr;

	ptr = malloc(sizeof(t_node));
	if (!ptr)
		return (NULL);
	if (ptr)
	{
		ptr->number = philosopher_number;
		ptr->next = NULL;
        ptr->prev = NULL;
        ptr->rules = rules;
		ptr->mutex = mutex;
	}
	return (ptr);
}

int	list_size(t_node *begin_list)
{
	int			i;
	t_node		*index;

	index = begin_list;
	i = 0;
	while (index)
	{
		i++;
		index = index -> next;
	}
	return (i);
}

t_node *list_last(t_node *head)
{
    t_node *node;

    if (!head)
        return NULL;

    node = head;
    while (node->next != head && node->next != NULL)
	{
        node = node->next;
	}
    return node;
}

void	append_item(t_node **ptr, int ph_nb, t_rules *rules, t_mutex *mutex)
{
	t_node	*last;
	t_node	*item;

	if (!ptr)
		return ;
	item = create_elem(ph_nb, rules, mutex);
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
	last->next->next = *ptr;
}