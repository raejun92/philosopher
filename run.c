#include "philo.h"

// 기능: 포크를 잡음, 리턴: 잘 집었으면 0, 누가 죽거나 같은 포크를 집을 경우 1
int	grap_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (send_message(philo, 1) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (send_message(philo, 1) == 1)
	{
		drop_fork(philo);
		return (1);
	}
	return (0);
}

// 기능: 음식을 먹음, 리턴: 잘 먹을 경우 0, 누가 죽으면 1
int	have_a_meal(t_philo *philo)
{
	if (grap_fork(philo) == 1)
		return (1);
	if (send_message(philo, 2) == 1)
	{
		drop_fork(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->data->only_one_death);
	philo->eat_cnt++;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->only_one_death);
	while (philo->data->check_death == 0 && (int)(get_current_time() - philo->last_meal_time) < philo->data->time_to_eat)
		usleep(500);
	if (philo->data->must_eat == philo->eat_cnt || philo->data->check_death == 1)
	{
		drop_fork(philo);
		return (1);
	}
	drop_fork(philo);
	return (0);
}

// 기능: 누가 죽었는지 모니터링, 리턴: void *
void	*is_alive(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo*)tmp;
	while (philo->data->check_death == 0 && philo->eat_cnt != philo->data->must_eat)
	{
		if (philo->data->check_death == 0 && (int)(get_current_time() - philo->last_meal_time) > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->only_one_death);
			philo->data->check_death++;
			send_message(philo, 0);
			pthread_mutex_unlock(&philo->data->only_one_death);
		}
		usleep(100);
	}
	return (NULL);
}

// 기능: 스레드는 포크를 집고 먹거나, 자거나, 생각하거나 죽거나 함, 리턴: void
void *run_thread(void *tmp)
{
	t_philo			*philo;
	pthread_t		monitor;
	unsigned long	before_sleep;

	philo = (t_philo*)tmp;
	pthread_create(&monitor, NULL, is_alive, philo);
	if (philo->name % 2 == 0)
		usleep(philo->data->time_to_eat);
	while (philo->data->check_death == 0)
	{
		if (have_a_meal(philo) == 1)
			break ;
		if (send_message(philo, 3) == 1)
			break ;
		before_sleep = get_current_time();
		while (philo->data->check_death == 0 && (int)(get_current_time() - before_sleep) < philo->data->time_to_sleep)
			usleep(500);
		if (send_message(philo, 4) == 1)
			break ;
		usleep(500);
	}
	pthread_join(monitor, NULL);
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