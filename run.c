#include "philo.h"

// static int	only_one_philo(t_philo *philo)
// {
// 	if (philo->l_fork == philo->r_fork)
// 	{
// 		pthread_mutex_lock(philo->l_fork);

// 	}
// }

void	spend_time(unsigned long time)
{
	unsigned long work_time;

	work_time = get_current_time() + time; // 현재시간에서 time만큼 자거나 먹는다
	while (work_time > get_current_time())
		usleep(100);
}

void	grap_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	send_message(philo, 1);
	pthread_mutex_lock(philo->r_fork);
	send_message(philo, 1);
}

void	have_a_meal(t_philo *philo)
{
	int i;

	philo->last_meal_time = get_current_time();
	send_message(philo, 2);
	spend_time(philo->data->time_to_eat);
	philo->eat_cnt++;
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*is_alive(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo*)tmp;
	while (1)
	{
		if (philo->data->check_death == 1 || philo->eat_cnt == philo->data->must_eat)
			break ;
		pthread_mutex_lock(&philo->data->only_one_death);
		if (get_current_time() - philo->last_meal_time > philo->data->time_to_die)
		{
			philo->data->check_death = 1;
			pthread_mutex_unlock(philo->l_fork);
			if (philo->data->check_death == 1)
			break ;
			send_message(philo, 0);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->only_one_death);
		usleep(20);
	}
	return (NULL);
}

// 기능: 스레드는 포크를 집고 먹거나, 자거나, 생각하거나 죽거나 함, 리턴: void
void *run_thread(void *tmp)
{
	t_philo	*philo;
	pthread_t	monitor;

	philo = (t_philo*)tmp;
	pthread_create(&monitor, NULL, is_alive, philo);
	// if (only_one_philo(philo))
	// 	return (0);
	if (philo->name % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (42)
	{
		if (philo->data->check_death == 1)
			break ;
		grap_fork(philo);
		if (philo->data->check_death == 1)
			break ;
		have_a_meal(philo);
		if (philo->data->check_death == 1)
			break ;
		drop_fork(philo);
		if (philo->data->check_death == 1)
			break ;
		if (philo->data->must_eat == philo->eat_cnt)
			break ;
		send_message(philo, 3);
		if (philo->data->check_death == 1)
			break ;
		spend_time(philo->data->time_to_sleep);
		if (philo->data->check_death == 1)
			break ;
		send_message(philo, 4);
		if (philo->data->check_death == 1)
			break ;
	}
	pthread_join(monitor, NULL);
	return (0);
}

// 기능: philo의 각 스레드를 동작 시킴, 리턴: void
void	run_philo(t_philo *philo)
{
	int 		i;

	i = -1;
	philo->data->start_time = get_current_time();
	while (++i < philo->data->people)
	{
		philo[i].last_meal_time = philo->data->start_time;
		pthread_create(&(philo[i].thread), NULL, run_thread, &(philo[i]));
		usleep(10);
	}
	i = -1;
	while (++i < philo->data->people)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo->data->fork[i]);
	}
	pthread_mutex_destroy(&philo->data->only_one_death);
	pthread_mutex_destroy(&philo->data->output);
}