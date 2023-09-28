#include <philo_r.h>

static void	init_philos(t_data *data)
{
	int	tmp;

	tmp = data->num;
	while (tmp--)
	{
		data->philos[tmp].num = data->num;
		data->philos[tmp].die = data->die;
		data->philos[tmp].eat = data->eat;
		data->philos[tmp].sleep = data->sleep;
		data->philos[tmp].max_eat = data->max_eat;
		data->philos[tmp].n = tmp;
		data->philos[tmp].side = data->num % 2;
		data->philos[tmp].loop = &data->loop;
		data->philos[tmp].total_meals = &data->meals;
		data->philos[tmp].forks[0] = &data->forks[tmp];
		data->philos[tmp].forks[1] = &data->forks[(tmp + 1) % data->num];
		data->philos[tmp].forks_mutex[0] = &data->forks_mutex[tmp];
		data->philos[tmp].forks_mutex[1] = &data->forks_mutex[(tmp + 1)
			% data->num];
		data->philos[tmp].loop_mutex = &data->loop_mutex;
		data->philos[tmp].print_mutex = &data->print_mutex;
	}
}

static void	init_mutexes(t_data *data)
{
	int	tmp;

	tmp = data->num;
	pthread_mutex_init(&data->loop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	while (tmp--)
		pthread_mutex_init(&data->forks_mutex[tmp], NULL);
}

static void	init_threads(t_data *data)
{
	int			tmp;
	long long	init_time;

	init_time = get_milliseconds();
	tmp = data->num;
	while (tmp--)
	{
		data->philos[tmp].t_0 = init_time;
		data->philos[tmp].last_meal = init_time;
		pthread_create(&data->philos_t[tmp], NULL, philo_routine,
			&data->philos[tmp]);
	}
	tmp = data->num;
	while (tmp--)
		pthread_join(data->philos_t[tmp], NULL);
}

int	init_data(t_data *data)
{
	init_philos(data);
	init_mutexes(data);
	init_threads(data);
	return (0);
}
