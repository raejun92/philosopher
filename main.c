#include "philo.h"

/* 
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

식사를 마치면 포크를 내려놓고 잠을 잔다
잠을 다 자면 생각한다
생각 후 식사한다
 */

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

void	init_philo(t_philo *philo, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		philo[i].name = i + 1;
		philo[i].eat_cnt = 0;
		philo[i].death = 0;
	}
}

int	parse_input(t_input *data, char *argv[])
{
	data->people = ft_atoi(argv[1]);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->people);
	// philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!data->fork)
		return (0);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->must_eat = -1;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	// init_philo(philo, data->people);
	return (1);
}

int main(int argc, char *argv[])
{
	t_input	data;
	t_philo	*philo;

	if (!check_input(argc, argv))
	{
		printf("input Error\n");
		exit(0);
	}
	if (!parse_input(&data, argv))
	{
		printf("parsing Error\n");
		exit(0);
	}
	philo = malloc(sizeof(philo) * data.people);
	init_philo(philo, data.people);
	printf("hello\n");
	printf("%d\n", philo[1].death);
	return (0);
}