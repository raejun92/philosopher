#include "philo.h"

// 기능: argv가 숫자인지 4~5개 인자인지 확인, 리턴: int (맞으면 1 아니면 0)
static int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
			if (!ft_isdigit(argv[i][j]))
				return (0);
		if (ft_atoi(argv[i]) <= 0)
			return (0);
	}
	return (1);
}

// 기능: 필로에 대한 값 초기화, 리턴: void
static void	init_philo(t_philo *philo, t_input *data)
{
	int	i;

	i = -1;
	while (++i < data->people)
	{
		philo[i].name = i + 1;
		philo[i].eat_cnt = 0;
		philo[i].data = data;
		philo[i].last_meal_time = 0;
		philo[i].l_fork = &(data->fork[i]);
		if (i == data->people - 1)
			philo[i].r_fork = &(data->fork[0]);
		else
			philo[i].r_fork = &(data->fork[i + 1]);
	}
}


// 기능: input으로 들어온 값 파싱, 리턴: 성공 1, 실패 0
static int	parse_input(t_input *data, char *argv[])
{
	data->people = ft_atoi(argv[1]);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->people);
	if (!data->fork)
		return (0);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	data->check_death = 0;
	data->start_time = 0;
	return (1);
}

// 기능: 동적 할당한 변수 할당 해제, 리턴: void
void	free_philo(t_philo *philo)
{
	if (philo->data->fork != 0)
		free(philo->data->fork);
	if (philo != 0)
		free(philo);
}

int main(int argc, char *argv[])
{
	t_input	data;
	t_philo	*philo;
	int		i;

	if (!check_input(argc, argv))
		return (process_error("input"));
	if (!parse_input(&data, argv))
		return (process_error("parse"));
	i = -1;
	while (++i < data.people)
		pthread_mutex_init(&data.fork[i], NULL);
	pthread_mutex_init(&data.output, NULL);
	pthread_mutex_init(&data.only_one_death, NULL);
	philo = malloc(sizeof(philo) * data.people);
	if (!philo)
		return (process_error("malloc"));
	init_philo(philo, &data);
	run_philo(philo);
	free_philo(philo);
	return (0);
}