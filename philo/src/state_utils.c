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

long long get_last_meal(t_philo philo)
{
	long long tmp;

	pthread_mutex_lock(&philo.my_mutex);
	tmp = philo.last_meal;
	pthread_mutex_unlock(&philo.my_mutex);
	return (tmp);
}

void	change_state(t_philo *philo)
{
	if (philo->state == THINK)
		philo->state = EAT;
	else if (philo->state == EAT)
		philo->state = SLEEP;
	else if (philo->state == SLEEP)
		philo->state = THINK;
}

void	set_dead(t_philo *philo)
{
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		philo->state = DEAD;
		print_state(philo, "died");
		pthread_mutex_lock(philo->loop_mutex);
		*philo->loop = 0;
		pthread_mutex_unlock(philo->loop_mutex);
	}
}