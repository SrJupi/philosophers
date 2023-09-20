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

# include <pthread.h>

typedef struct  s_philo
{
    int n;
    int die;
    int eat;
    int sleep;
    int n_eat;
    long long   when_I_was_born;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philo;

typedef struct s_data
{
    int num;
    int die;
    int eat;
    int sleep;
    int n_eat;
}   t_data;

typedef struct s_cmd
{
    /* data */
}   t_cmd;



// Check philo parameters
int check_args(int argc, char **argv, t_data *data);

// Routines
void    *philo_routine(void *arg);

// Time stuff
long long	get_milliseconds(void);

#endif
