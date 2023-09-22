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

static t_philo	**create_philos(t_data data, int *loop, pthread_mutex_t *check)
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
			tmp[i]->num_philos = data.num;
			tmp[i]->n_eat = 0;
			tmp[i]->loop = loop;
			tmp[i]->check_mutex = check;
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
		philos[i]->left_fork = &forks[i] ;
		philos[i]->right_fork = &forks[(i + 1) % num];
		i++;
	}
}

t_cmd	*create_cmd(t_data data)
{
	t_cmd *tmp;
	pthread_mutex_t check;

	tmp = (t_cmd *) malloc (sizeof(t_cmd));
	if (tmp != NULL)
	{
		pthread_mutex_init(&check, NULL);
		tmp->loop = 1;
		tmp->n_philo = data.num;
		tmp->max_meal = data.n_eat;
		tmp->check_mutex = &check;
	}
	return (tmp);
}

void init_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void init_philo(t_data data)
{
	t_philo 	**philos;
	t_cmd		*cmd_struct;
	pthread_t	*philos_t;
	pthread_t	cmd;
 	pthread_mutex_t *forks;

	cmd_struct = create_cmd(data);
	philos = create_philos(data, &cmd_struct->loop, cmd_struct->check_mutex);
	if (philos == NULL)
		printf("MALLOC FAILED");
	cmd_struct->philos = philos;
	philos_t = (pthread_t *) malloc (sizeof(pthread_t) * data.num);
	forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * data.num);
	if (philos_t && forks)
	{
		delivery_forks(philos, forks, data.num);
		init_forks(forks, data.num);
	}
	else
	{
		clean_philos(philos, data.num);
	}
	int i = 0;
	while (i < data.num)
	{	
		philos[i]->t_0 = get_milliseconds();
    	philos[i]->last_meal = philos[i]->t_0;
		pthread_create(&philos_t[i], NULL, philo_routine, philos[i]);
		i++;
	}
	pthread_create(&cmd, NULL, cmd_routine, cmd_struct);
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
		init_philo(data);	
}
