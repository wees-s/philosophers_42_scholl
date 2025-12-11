#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

//mutex
typedef struct s_mutex
{
    pthread_mutex_t	*hashi;
}   t_mutex;


//info_philosophers
typedef struct s_rules
{
    //quantidade de filósofos
    int             ph_quantity;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            start_time;
}   t_rules;

//philosopher_node
typedef struct s_node
{
    t_mutex         *mutex;
    pthread_t       thread_id;//thread do filósofo
    t_rules         *rules;//regras de vida
    pthread_mutex_t	*left;//hashi da esquerda
	pthread_mutex_t	*right;//hashi da direita
    int             number;//número/nome do filósofo
	struct s_node	*next;
	struct s_node	*prev;
}   t_node;

//list_utils
int	    list_size(t_node *begin_list);
t_node	*create_elem(int philosopher_number, t_rules *rules, t_mutex *mutex);
t_node  *list_last(t_node *head);
void	append_item(t_node **ptr, int ph_nb, t_rules *rules, t_mutex *mutex);

//auxiliar_functions
int		ft_atoi(const char *string);

//parser
void    print_error(char **argv);
int     valid_input(char **argv);

//philosophers
void    init_philo(t_rules *rules, char **argv, t_node **nodes);
void    threads_and_mutexes(t_node **nodes);
void    *routine(void *ptr);

//main
long	get_time(void);
void	join_all_threads(t_node **nodes);

#endif