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

#include <philo_r.h>

void	set_dead(t_philo *philo)
{
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		print_state(philo, "died");
		zero_loop(philo->loop_mutex, philo->loop);
	}
}
