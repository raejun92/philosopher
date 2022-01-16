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
	pthread_mutex_t	*output;
	int				people;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat; // 모든 철학자가 먹어야 함
	unsigned long	start_time;
}t_input;

typedef struct	s_philo
{
	pthread_t		thread;
	int				name;
	int				eat_cnt;
	int				death;
}t_philo;

/* ft_util.c */
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif