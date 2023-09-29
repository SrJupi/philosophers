/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:45:12 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 15:45:14 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	clean_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->loop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while (i < data->num)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	return (1);
}

int	clean_data(t_data *data)
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
