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
	if (philo->state == INIT || philo->state == THINK)
		philo->state = EAT;
	else if (philo->state == EAT)
		philo->state = SLEEP;
	else if (philo->state == SLEEP)
		philo->state = THINK;
}

void	print_state(long long current_time, int philo, const char *status)
{
	printf("%lld ms %d is %s!\n", current_time, philo, status);
}
