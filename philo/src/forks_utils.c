/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:45:18 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 15:45:22 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks_mutex[philo->side]);
	pthread_mutex_lock(philo->forks_mutex[(philo->side + 1) % 2]);
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks_mutex[philo->side]);
	pthread_mutex_unlock(philo->forks_mutex[(philo->side + 1) % 2]);
}

int	try_get_forks(t_philo *philo)
{
	int	fork1;
	int	fork2;

	fork1 = 0;
	fork2 = 0;
	while (!fork1 || !fork2)
	{
		am_i_dead(philo);
		lock_forks(philo);
		if (*philo->forks[0])
		{
			*philo->forks[0] = 0;
			print_state(philo, "has taken left fork");
			fork1 = 1;
		}
		if (*philo->forks[1])
		{
			*philo->forks[1] = 0;
			print_state(philo, "has taken right fork");
			fork2 = 1;
		}
		unlock_forks(philo);
	}
	return (1);
}

void	return_forks(t_philo *philo)
{
	lock_forks(philo);
	*philo->forks[0] = 1;
	*philo->forks[1] = 1;
	unlock_forks(philo);
}
