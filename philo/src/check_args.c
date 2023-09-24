#include <philo.h>

static int	ft_isnum(const char *str)
{
	while (*str)
	{
		if ((*str) < '0' || (*str) > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	check_argv(int argc, char **argv)
{
	while (--argc > 0)
	{
		if (!ft_isnum(argv[argc]))
			return (1);
	}
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	num;

	num = 0;
	while (*str)
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num);
}

static int	create_data(int argc, char **argv, t_data *data)
{
	data->num = ft_atoi(argv[1]);
	if (!data->num || data->num > 200)
		return (1);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	else
		data->max_eat = -1;
	data->loop = 1;
	data->meals = 0;
	return (0);
}

int	check_args(int argc, char **argv, t_data *data)
{
	(void)data;
	if (argc < 5 || argc > 6)
		return (1);
	if (check_argv(argc, argv))
		return (1);
	if (create_data(argc, argv, data))
		return (1);
	return (0);
}