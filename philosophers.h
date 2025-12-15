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
    pthread_mutex_t	write_lock;
    pthread_mutex_t	meal_lock;
    pthread_mutex_t time_lock;
    pthread_mutex_t max_meal_lock;
}   t_mutex;


//info_philosophers
typedef struct s_rules
{
    int             dead;
    int             ph_quantity;
    int             max_meals;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            time_to_think;
    long            start_time;
    long            real_time;
    pthread_t       monitor;
}   t_rules;

//philosopher_node
typedef struct s_node
{
    t_mutex         *mutex;
    pthread_t       thread_id;
    t_rules         *rules;
    pthread_mutex_t	*left;
	pthread_mutex_t	*right;
    int             number;
    long            last_meal;
    int             meals;
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

//main
long	get_time(void);
void	join_all_threads(t_node **nodes);

//routine
void    *routine(void *ptr);
void    *monitor(void *head);

//routine_utils
void    take_hashis(t_node *ptr);
void    put_hashis(t_node *ptr);
void    eat(t_node *ptr);
void    philosophers_sleep(t_node *ptr);
void    think(t_node *ptr);

//free_all
void    free_list(t_node **begin_list);

#endif