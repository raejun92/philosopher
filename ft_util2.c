#include "philo.h"

void	send_message(t_philo *philo, int status)
{
	unsigned long	output_time;

	pthread_mutex_lock(&philo->data->output);
	output_time = get_current_time() - philo->data->start_time;
	if (philo->data->check_death == 0)
	{
		if (status == 1)
			printf("%lu %d has taken a fork\n", output_time, philo->name);
		else if (status == 2)
			printf("%lu %d is eating\n", output_time, philo->name);
		else if (status == 3)
			printf("%lu %d is sleeping\n", output_time, philo->name);
		else if (status == 4)
			printf("%lu %d is thinking\n", output_time, philo->name);
	}
	else
		printf("%lu %d died\n", output_time, philo->name);
	pthread_mutex_unlock(&philo->data->output);
}