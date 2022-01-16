#include "philo.h"

int	process_error(char *str)
{
	printf("%s error\n", str);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' ||
			c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] != '\0' && is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (num * sign > 2147483647)
			return (-1);
		if (num * sign < -2147483648)
			return (-1);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

unsigned long	get_current_time(void)
{
	struct timeval	tmp;
	unsigned long	milisecond;

	if (gettimeofday(&tmp, NULL) == -1)
		process_error("gettimeofday");
	milisecond = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	return (milisecond);
}