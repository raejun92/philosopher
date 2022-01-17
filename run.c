#include "philo.h"

// static int	only_one_philo(t_philo *philo)
// {
// 	if (philo->l_fork == philo->r_fork)
// 	{
// 		pthread_mutex_lock(philo->l_fork);

// 	}
// }

static int	grap_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	send_message(philo, 1);
	// TODO: here
	return (0);
}

// 기능: 스레드는 포크를 집고 먹거나, 자거나, 생각하거나 죽거나 함, 리턴: void
static void *run_thread(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo*)tmp;
	// if (only_one_philo(philo))
	// 	return (0);
	if (philo->name % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (1)
	{
		if (philo->data->check_death == 1)
			break ;
		if (grap_fork_and_eat(philo) == 1)
			break ;
	}
	return (0);
}

// 기능: philo의 각 스레드를 동작 시킴, 리턴: void
void	run_philo(t_philo *philo)
{
	int i;

	i = -1;
	philo->data->start_time = get_current_time();
	while (++i < philo->data->people)
	{
		philo[i].last_meal_time = philo->data->start_time;
		pthread_create(&(philo[i].thread), NULL, run_thread, &(philo[i]));
	}
}