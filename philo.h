#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_input
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	output;
	pthread_mutex_t	only_one_death;
	int				people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				check_death;
	unsigned long	start_time;
}t_input;

typedef struct	s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	int				name;
	int				eat_cnt;
	unsigned long	last_meal_time;
	t_input			*data;
}t_philo;

/* ft_util.c */
int				process_error(char *str);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
unsigned long	get_current_time(void);

/* ft_util2.c */
void			send_message(t_philo *philo, int status);

/* run.c */
void			run_philo(t_philo *philo);
#endif