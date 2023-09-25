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

#include <philo.h>

static void clean_philos(t_philo **philos, int i)
{
	while (i--)
		free(philos[i]);
	free(philos);
}

static t_philo	**create_philos(t_data data, int *loop, int *all_foods)
{
	t_philo	**tmp;
	int		i;
	pthread_mutex_t loop_mutex;
	pthread_mutex_t meals_mutex;
	pthread_mutex_t print_mutex;

	i = 0;
	tmp = (t_philo **)malloc(sizeof(t_philo *) * data.num);
	if (tmp != NULL)
	{
		while (i < data.num)
		{
			tmp[i] = (t_philo *)malloc(sizeof(t_philo));
			if (tmp[i] == NULL)
			{
				clean_philos(tmp, i);
				return (NULL);
			}
			tmp[i]->n = i;
			tmp[i]->data = &data;
			tmp[i]->loop = loop;
			tmp[i]->total_meals = all_foods;
			tmp[i]->loop_mutex = &loop_mutex;
			tmp[i]->meals_mutex = &meals_mutex;
			tmp[i]->print_mutex = &print_mutex;
			tmp[i]->state = THINK;
			tmp[i]->side = i % 2;
			i++;
		}
	}
	return (tmp);
}

void	delivery_forks(t_philo **philos, pthread_mutex_t *forks_mutex, int *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i]->forks_mutex[0] = &forks_mutex[i];
		philos[i]->forks[0] = &forks[i];
		philos[i]->forks_mutex[1]= &forks_mutex[(i + 1) % num];
		philos[i]->forks[1] = &forks[(i + 1) % num];
		i++;
	}
}

void	init_mutex(pthread_mutex_t *forks_mutex, int num, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(philo->loop_mutex, NULL);
	pthread_mutex_init(philo->meals_mutex, NULL);
	pthread_mutex_init(philo->print_mutex, NULL);

}

void fill_forks(int *forks, int size)
{
	for (int i = 0; i < size; i++)
	{
		forks[i] = 1;
	}
	
}

void	init_philo(t_data data)
{
	t_philo			**philos;
	pthread_t		*philos_t;
	pthread_mutex_t	*forks_mutex;
	int				loop;
	int				*forks;
	int				i;
	int				all_foods;

	
	loop = 1;
	all_foods = 0;
	philos = create_philos(data, &loop, &all_foods);
	if (philos == NULL)
		printf("MALLOC FAILED");
	philos_t = (pthread_t *)malloc(sizeof(pthread_t) * data.num);
	forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.num);
	forks = (int *) malloc (sizeof(int) * data.num);
	fill_forks(forks, data.num);
	if (philos_t && forks_mutex)
	{
		delivery_forks(philos, forks_mutex, forks, data.num);
		init_mutex(forks_mutex, data.num, philos[0]);
	}
	else
	{
		clean_philos(philos, data.num);
	}
	i = 0;
	long long init_time = get_milliseconds();
	while (i < data.num)
	{
		philos[i]->t_0 = init_time;
		philos[i]->last_meal = init_time;
		pthread_create(&philos_t[i], NULL, philo_routine, philos[i]);
		i++;
	}
	i = 0;
	while (i < data.num)
	{
		pthread_join(philos_t[i], NULL);
		i++;
	}
	clean_philos(philos, data.num);
	free(forks_mutex);
}

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



int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv, &data))
		print_usage();
	else
		init_philo(data);
}
