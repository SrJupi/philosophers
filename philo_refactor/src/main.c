/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:36:19 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 18:56:29 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_r.h>

void	print_usage(void)
{
	printf("Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[<number_of_times_each_philosopher_must_eat>]\n");
	printf("\n");
	printf("Description:\n");
	printf("  Simulate the dining philosophers problem with \
specified parameters.\n");
	printf("\n");
	printf("Example:\n");
	printf("  philo 5 800 200 200\n");
	printf("  philo 4 410 200 200 5\n");
}

void	fill_forks(int *forks, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		forks[i] = 1;
		i++;
	}
}

int	malloc_data(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num);
	data->philos_t = (pthread_t *)malloc(sizeof(pthread_t) * data->num);
	data->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num);
	data->forks = (int *)malloc(sizeof(int) * data->num);
	if (!data->philos || !data->philos_t || !data->forks_mutex || !data->forks)
		return (clean_data(data));
	fill_forks(data->forks, data->num);
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
	else if (init_data(&data))
		clean_data(&data);
	else
	{
		clean_mutexes(&data);
		clean_data(&data);
	}
}
