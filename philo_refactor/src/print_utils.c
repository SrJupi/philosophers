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

#include <philo_r.h>

/* static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
} */

static void	print_well_fed(t_philo *philo)
{
	zero_loop(philo->loop_mutex, philo->loop);
	printf("Simulation ended at %lld because all philosophers were full.\n",
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
		printf("%lld %d %s - side: %d\n", tmp - philo->t_0, philo->n, status);
		if (philo->max_eat > 0 && philo->state == EAT)
			check_all_meals(philo);
	}
	pthread_mutex_unlock(philo->print_mutex);
	return (tmp);
}
