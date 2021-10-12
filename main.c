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
		if (ft_atoi(argv[i]) < 0)
			return (0);
	}
	return (1);
}

int main(int argc, char *argv[])
{
	if (!check_input(argc, argv))
		exit(0);
	printf("good\n");
	return (0);
}