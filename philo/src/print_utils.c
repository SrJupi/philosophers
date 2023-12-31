/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:46:52 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 15:46:53 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	print_well_fed(t_philo *philo)
{
	zero_loop(philo->loop_mutex, philo->loop);
	printf("Simulation ended at %lld ms because all philosophers were full.\n",
		get_milliseconds() - philo->t_0);
}

static void	check_all_meals(t_philo *philo)
{
	philo->meals += 1;
	if (philo->meals == philo->max_eat)
	{
		*philo->total_meals += 1;
		if (*philo->total_meals == philo->num)
			print_well_fed(philo);
	}
}

long long	print_state(t_philo *philo, const char *status)
{
	long long	tmp;

	tmp = 0;
	pthread_mutex_lock(philo->print_mutex);
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		tmp = get_milliseconds();
		printf("%6lld ms -> philosopher %03d %s\n", \
		tmp - philo->t_0, philo->n, status);
		if (philo->max_eat > 0 && philo->state == EAT)
			check_all_meals(philo);
		if (philo->state == DEAD)
			zero_loop(philo->loop_mutex, philo->loop);
	}
	pthread_mutex_unlock(philo->print_mutex);
	return (tmp);
}
