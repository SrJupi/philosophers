#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void    ph_eat(t_philo *philo)
{
    long long   eat_init;
    
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    change_state(philo);
    eat_init = get_milliseconds();
    pthread_mutex_lock(philo->check_mutex);
    if (*philo->loop)
    {
        philo->last_meal = eat_init;
        print_state(eat_init - philo->t_0, philo->n, "eating");
    }
    pthread_mutex_unlock(philo->check_mutex);
    while (get_milliseconds() - eat_init < (long long)philo->eat)
        ;
    pthread_mutex_lock(philo->check_mutex);
    philo->n_eat += 1;
    pthread_mutex_unlock(philo->check_mutex);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    ph_sleep(t_philo *philo)
{
    long long   sleep_init;
    
    sleep_init = get_milliseconds();
    pthread_mutex_lock(philo->check_mutex);
    if (*philo->loop)
    {
        print_state(sleep_init - philo->t_0, philo->n, "sleeping");
    }
    pthread_mutex_unlock(philo->check_mutex);
    change_state(philo);
    while (get_milliseconds() - sleep_init < philo->sleep)
        ;
}

void    ph_think(t_philo *philo)
{
    long long   think_init;

    change_state(philo);
    think_init = get_milliseconds() - philo->t_0;
    pthread_mutex_lock(philo->check_mutex);
    if (*philo->loop)
    {
        print_state(think_init, philo->n, "thinking");
    }
    pthread_mutex_unlock(philo->check_mutex);
}

void    do_routine(t_philo *philo)
{
    int     loop;

    loop = 1;
    while(loop)
    {
        if (philo->state == INIT || philo->state == THINK)
            ph_eat(philo);
        else if (philo->state == EAT)
            ph_sleep(philo);
        else if (philo->state == SLEEP)
            ph_think(philo);
        loop = get_loop(philo->check_mutex, philo->loop);    
    }
}

void    just_kill_me(t_philo *philo)
{
    int loop;
    
    loop = 1;
    while(loop)
        loop = get_loop(philo->check_mutex, philo->loop);
}

void    *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *) data;
    printf("philo %d started\n", philo->n);

    if (philo->num_philos == 1)
        just_kill_me(philo);
    else
        do_routine(philo);

    printf("philo %d finished\n", philo->n);

    return (NULL);
}