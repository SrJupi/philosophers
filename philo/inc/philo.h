/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:42:58 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/09/28 19:00:24 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

enum e_state
{
	EAT,
	THINK,
	SLEEP,
	DEAD,
};

typedef struct s_philo
{
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				max_eat;
	int				n;
	int				meals;
	enum e_state	state;
	long long		t_0;
	long long		last_meal;
	int				side;
	int				*loop;
	int				*total_meals;
	int				*forks[2];
	pthread_mutex_t	*forks_mutex[2];
	pthread_mutex_t	*loop_mutex;
	pthread_mutex_t	*print_mutex;
}					t_philo;

typedef struct s_data
{
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				max_eat;
	int				loop;
	pthread_mutex_t	loop_mutex;
	int				meals;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	pthread_t		*philos_t;
	pthread_mutex_t	*forks_mutex;
	int				*forks;
}					t_data;

// Check philo parameters
int					check_args(int argc, char **argv, t_data *data);

// Routines
void				*philo_routine(void *data);

// Time stuff
long long			get_milliseconds(void);

// Loop utils
int					get_loop(pthread_mutex_t *loop_mutex, int *current_loop);
void				zero_loop(pthread_mutex_t *loop_mutex, int *current_loop);

// State utils
void				set_dead(t_philo *philo);
void				change_state(t_philo *philo);

// Print utils
long long			print_state(t_philo *philo, const char *status);

int					try_get_forks(t_philo *philo);
void				return_forks(t_philo *philo);

void				am_i_dead(t_philo *philo);

int					init_data(t_data *data);

int					clean_data(t_data *data);
int					clean_mutexes(t_data *data);

#endif
