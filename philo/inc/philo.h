/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:42:58 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/20 13:43:22 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>

enum    e_state
{
    EAT,
    THINK,
    SLEEP,
    DEAD,
};

typedef struct s_data
{
    int num;
    int die;
    int eat;
    int sleep;
    int max_eat;
}   t_data;

typedef struct  s_philo
{
    int n;
    t_data *data;
    enum e_state state;
    long long   t_0;
    long long   last_meal;
    int side; 
    int *loop;
    int *total_meals;
    int *forks[2];
    pthread_mutex_t *forks_mutex[2];
    pthread_mutex_t *loop_mutex;
    pthread_mutex_t *print_mutex;
    pthread_mutex_t *meals_mutex;
}   t_philo;

// Check philo parameters
int check_args(int argc, char **argv, t_data *data);

// Routines
void    *philo_routine(void *data);

// Time stuff
long long	get_milliseconds(void);


int get_loop(pthread_mutex_t *loop_mutex, int *current_loop);

// Philo utils
void    change_state(t_philo *philo);
void	set_dead(t_philo *philo, long long time_of_dead);
void	print_state(long long current_time, t_philo *philo, const char *status);
void	check_all_meals(t_philo *philo);


int	    try_get_forks(t_philo *philo);
void    lock_forks(t_philo *philo);
void    unlock_forks(t_philo *philo);
void	return_forks(t_philo *philo);

void add_to_priority(t_philo *philo);
int is_priority(t_philo *philo);



#endif
