/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:45:38 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 15:45:40 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_r.h>

int	get_loop(pthread_mutex_t *loop_mutex, int *current_loop)
{
	int	ret;

	pthread_mutex_lock(loop_mutex);
	ret = *current_loop;
	pthread_mutex_unlock(loop_mutex);
	return (ret);
}

void	zero_loop(pthread_mutex_t *loop_mutex, int *current_loop)
{
	pthread_mutex_lock(loop_mutex);
	*current_loop = 0;
	pthread_mutex_unlock(loop_mutex);
}
