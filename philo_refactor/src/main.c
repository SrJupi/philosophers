/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:36:19 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/20 13:45:11 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_r.h>

void print_usage() {
    printf("Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[<number_of_times_each_philosopher_must_eat>]\n");
    printf("\n");
    printf("Description:\n");
    printf("  Simulate the dining philosophers problem with specified parameters.\n");
    printf("\n");
    printf("Example:\n");
    printf("  philo 5 800 200 200\n");
    printf("  philo 4 410 200 200 5\n");
}

void init_philos(t_data *data)
{
	int tmp = data->num;
	
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
		data->philos[tmp].forks_mutex[1] = &data->forks_mutex[(tmp + 1) % data->num];
		data->philos[tmp].loop_mutex = &data->loop_mutex;
		data->philos[tmp].print_mutex = &data->print_mutex;
	}
}

void	init_mutexes(t_data *data)
{
	int tmp;
	
	tmp = data->num;
	pthread_mutex_init(&data->loop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	while (tmp--)
		pthread_mutex_init(&data->forks_mutex[tmp], NULL);
}

void	init_threads(t_data *data)
{
	int tmp;
	long long init_time;
	
	init_time = get_milliseconds();
	tmp = data->num;
	while (tmp--)
	{
		data->philos[tmp].t_0 = init_time;
		data->philos[tmp].last_meal = init_time;
		pthread_create(&data->philos_t[tmp], NULL, philo_routine, &data->philos[tmp]);
	}
	tmp = data->num;
	while (tmp--)
		pthread_join(data->philos_t[tmp], NULL);
}

void	init_data(t_data *data)
{
	init_philos(data);
	init_mutexes(data);
	init_threads(data);
}

int clean_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->philos_t)
		free(data->philos_t);
	if (data->forks_mutex)
		free(data->forks_mutex);
	if (data->forks)
		free(data->forks);
	return (1);
}


int malloc_data(t_data *data)
{
	data->philos = (t_philo *) malloc (sizeof(t_philo) * data->num);
	data->philos_t = (pthread_t *) malloc (sizeof(pthread_t) * data->num);
	data->forks_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * data->num);
	data->forks = (int *) malloc (sizeof(int) * data->num);
	if (!data->philos || !data->philos_t || !data->forks_mutex || !data->forks)
		return (clean_data(data));
	memset(data->forks, 1, sizeof(int) * data->num);
	memset(data->philos, 0, sizeof(t_philo) * data->num);
	return (0);
}


int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (check_args(argc, argv, &data))
		print_usage();
	else if (malloc_data(&data))
		clean_data(&data);
	else
	{
		init_data(&data);
		clean_data(&data);
	}

}
