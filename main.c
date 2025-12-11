#include "philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	join_all_threads(t_node **nodes)
{
	t_node	*start;
	t_node	*curr;

	start = (*nodes);
	curr = (*nodes);
	if (!curr)
		return ;
	while (1)
	{
		pthread_join(curr->thread_id, NULL);
		curr = curr->next;
		if (curr == start)
			break ;
	}
}

int main(int argc, char **argv)
{
    t_rules rules;
    t_node  *nodes;

    if (argc == 5)
    {
        if (ft_atoi(argv[1]) < 1 || !valid_input(argv))
            print_error(argv);
    }
    else
    {
        printf("Error: Philosophers need 4 arguments.\n");
        exit(EXIT_FAILURE);
    }
    printf("teste1\n");
    init_philo(&rules, argv, &nodes);
    threads_and_mutexes(&nodes);
    nodes->rules->start_time = get_time();
    join_all_threads(&nodes);









    //GEPETECO
    t_node *tmp = nodes;
    int     first = 1;

    if (!tmp)
    {
        printf("Lista vazia.\n");
        return (0);
    }

    while (tmp && (tmp != nodes || first))
    {
        first = 0;

        printf("=== FILÓSOFO %d ===\n", tmp->number);
        printf("thread_id:        %p\n", (void *)tmp->thread_id);
        printf("rules:            %p\n", (void *)tmp->rules);
        printf("mutex struct:     %p\n", (void *)tmp->mutex);

        if (tmp->left)
            printf("left fork:        %p\n", (void *)tmp->left);
        else
            printf("left fork:        NULL\n");

        if (tmp->right)
            printf("right fork:       %p\n", (void *)tmp->right);
        else
            printf("right fork:       NULL\n");

        printf("next:             %p\n", (void *)tmp->next);
        printf("prev:             %p\n", (void *)tmp->prev);

        printf("---------------------------\n");

        tmp = tmp->next;
    }
    //GEPETECO









    return (0);
}