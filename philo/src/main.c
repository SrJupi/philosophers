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

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	clean_philos(t_philo **philos, int i)
{
	while (i--)
		free(philos[i]);
	free(philos);
}

static t_philo	**create_philos(t_data data)
{
	t_philo	**tmp;
	int		i;

	i = 0;
	tmp = (t_philo **) malloc (sizeof(t_philo *) * data.num);
	if (tmp != NULL)
	{
		while (i < data.num)
		{
			tmp[i] = (t_philo *) malloc (sizeof(t_philo));
			if (tmp[i] == NULL)
			{
				clean_philos(tmp, i);
				return (NULL);
			}
			tmp[i]->n = i;
			tmp[i]->die = data.die;
			tmp[i]->eat = data.eat;
			tmp[i]->sleep = data.sleep;
			tmp[i]->n_eat = data.n_eat;
			i++;
		}
	}
	return (tmp);
}

void delivery_forks(t_philo **philos, pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i]->left_fork = &forks[(i + num - 1) % num] ;
		philos[i]->right_fork = &forks[(i + 1) % num];
		i++;
	}
}

void init_philo(t_data data)
{
	t_philo 	**philos;
	pthread_t	*philos_t;
	//pthread_t	cmd;
 	pthread_mutex_t *forks;

	philos = create_philos(data);
	if (philos == NULL)
		printf("MALLOC FAILED");
	philos_t = (pthread_t *) malloc (sizeof(pthread_t) * data.num);
	forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * data.num);
	if (philos_t && forks)
	{
		delivery_forks(philos, forks, data.num);
	}
	else
	{
		clean_philos(philos, data.num);
	}
	int i = 0;
	while (i < data.num)
	{	
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
	free(forks);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv, &data))
		printf("wrong\n");
	else
	{
		printf("DATA:\nnum - %d\ndie - %d\neat - %d\nsleep - %d\nnum eat - %d\n",
		data.num, data.die, data.eat, data.sleep, data.n_eat);
	}
	init_philo(data);
	
}
