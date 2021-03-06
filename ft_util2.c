#include "philo.h"

int	send_message(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->output);
	if (philo->data->check_death == 0 && status == 1)
		printf("%lu %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->name);
	else if (philo->data->check_death == 0 && status == 2)
		printf("%lu %d is eating\n", get_current_time() - philo->data->start_time, philo->name);
	else if (philo->data->check_death == 0 && status == 3)
		printf("%lu %d is sleeping\n", get_current_time() - philo->data->start_time, philo->name);
	else if (philo->data->check_death == 0 && status == 4)
		printf("%lu %d is thinking\n", get_current_time() - philo->data->start_time, philo->name);
	else if (philo->data->check_death == 1 && status == 0)
		printf("%lu %d died\n", get_current_time() - philo->data->start_time, philo->name);
	pthread_mutex_unlock(&philo->data->output);
	if (philo->data->check_death > 0)
		return (1);
	return (0);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}