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

enum    e_state
{
    INIT,
    EAT,
    THINK,
    SLEEP,
    DEAD
};

typedef struct  s_philo
{
    int n;
    int num_philos;
    int die;
    int eat;
    int sleep;
    int n_eat;
    enum e_state state;
    long long   t_0;
    long long   last_meal;
    int *loop;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *check_mutex;
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
    int loop;
    int max_meal;
    int n_philo;
    pthread_mutex_t *check_mutex;
    t_philo **philos;
}   t_cmd;



// Check philo parameters
int check_args(int argc, char **argv, t_data *data);

// Routines
void    *philo_routine(void *data);
void *cmd_routine(void *data);

// Time stuff
long long	get_milliseconds(void);

// Cmd utils
int get_loop(pthread_mutex_t *check_mutex, int *current_loop);
void loop_to_zero(pthread_mutex_t *check_mutex, int *current_loop);
void print_well_fed_message(pthread_mutex_t *check_mutex, int meals);

// Philo utils
void    change_state(t_philo *philo);
void	set_dead(t_philo *philo, long long time_of_dead);
void    print_state(long long current_time, int philo, const char *status);
long long get_last_meal(t_philo *philo);
int get_meals(t_philo *philo);


#endif
