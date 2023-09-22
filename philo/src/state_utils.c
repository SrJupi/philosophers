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

#include "philo.h"
#include <stdio.h>

void	change_state(t_philo *philo)
{	
	pthread_mutex_lock(philo->check_mutex);
	if (philo->state == INIT || philo->state == THINK)
		philo->state = EAT;
	else if (philo->state == EAT)
		philo->state = SLEEP;
	else if (philo->state == SLEEP)
		philo->state = THINK;
	pthread_mutex_unlock(philo->check_mutex);
}

void	set_dead(t_philo *philo, long long time_of_dead)
{	
	pthread_mutex_lock(philo->check_mutex);
	philo->state = DEAD;
	print_state(time_of_dead, philo->n, "dead");
	pthread_mutex_unlock(philo->check_mutex);
}

long long get_last_meal(t_philo *philo)
{
	long long tmp;
	
	pthread_mutex_lock(philo->check_mutex);
	tmp = philo->last_meal;
	pthread_mutex_unlock(philo->check_mutex);
	return (tmp);
}

int get_meals(t_philo *philo)
{
	int tmp;
	
	pthread_mutex_lock(philo->check_mutex);
	tmp = philo->n_eat;
	pthread_mutex_unlock(philo->check_mutex);
	return (tmp);
}

void	print_state(long long current_time, int philo, const char *status)
{
	printf("%lld ms - Philo %d is %s!\n", current_time, philo, status);
}

int get_loop(pthread_mutex_t *check_mutex, int *current_loop)
{
	int	ret;
	
	pthread_mutex_lock(check_mutex);
	ret = *current_loop;
    pthread_mutex_unlock(check_mutex);
	return (ret);
}

void loop_to_zero(pthread_mutex_t *check_mutex, int *current_loop)
{
	pthread_mutex_lock(check_mutex);
	*current_loop = 0;
    pthread_mutex_unlock(check_mutex);
}

void print_well_fed_message(pthread_mutex_t *check_mutex, int meals)
{
	pthread_mutex_lock(check_mutex);
	printf("Uhmm!!! All philosophers ate at least %d meals!!!\nBye bye!\n", meals);
	pthread_mutex_unlock(check_mutex);
}