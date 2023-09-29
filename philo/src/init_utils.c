/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:45:28 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 18:58:40 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
		data->philos[tmp].state = THINK;
		data->philos[tmp].side = tmp % 2;
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

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->loop_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	while (i < data->num)
	{
		if (pthread_mutex_init(&data->forks_mutex[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	init_threads(t_data *data)
{
	int			tmp;
	long long	init_time;

	init_time = get_milliseconds();
	tmp = 0;
	while (tmp < data->num)
	{
		data->philos[tmp].t_0 = init_time;
		data->philos[tmp].last_meal = init_time;
		pthread_create(&data->philos_t[tmp], NULL, philo_routine,
			&data->philos[tmp]);
		tmp++;
	}
	tmp = 0;
	while (tmp < data->num)
	{
		pthread_join(data->philos_t[tmp], NULL);
		tmp++;
	}
}

int	init_data(t_data *data)
{
	init_philos(data);
	if (init_mutexes(data))
		return (clean_mutexes(data));
	init_threads(data);
	return (0);
}
