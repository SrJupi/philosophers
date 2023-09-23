/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:57:04 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/21 09:58:36 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	change_state(t_philo *philo)
{
	if (philo->state == THINK)
		philo->state = EAT;
	else if (philo->state == EAT)
		philo->state = SLEEP;
	else if (philo->state == SLEEP)
		philo->state = THINK;
}

void	set_dead(t_philo *philo, long long time_of_dead)
{
	pthread_mutex_lock(philo->loop_mutex);
	if (*philo->loop)
	{
		philo->state = DEAD;
		*philo->loop = 0;
		print_state(time_of_dead - philo->t_0, philo, "dead");
	}
	pthread_mutex_unlock(philo->loop_mutex);
}

void	print_state(long long current_time, t_philo *philo, const char *status)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%lld %d is %s\n", current_time, philo->n, status);
	pthread_mutex_unlock(philo->print_mutex);
}

void	check_all_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->meals_mutex);
	*philo->total_meals += 1;
	if (philo->data->max_eat > 0 && *philo->total_meals > philo->data->max_eat * philo->data->num)
	{
		pthread_mutex_unlock(philo->meals_mutex);
		pthread_mutex_lock(philo->loop_mutex);
		*philo->loop = 0;
		pthread_mutex_unlock(philo->loop_mutex);
	}
	else
		pthread_mutex_unlock(philo->meals_mutex);		
}

int	get_loop(pthread_mutex_t *loop_mutex, int *current_loop)
{
	int	ret;

	pthread_mutex_lock(loop_mutex);
	ret = *current_loop;
	pthread_mutex_unlock(loop_mutex);
	return (ret);
}