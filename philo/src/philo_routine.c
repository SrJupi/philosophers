#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int    check_dead(t_philo *philo)
{
    long long tmp;

    tmp = get_milliseconds();
    if (tmp - philo->last_meal > (long long)philo->die)
    {
        pthread_mutex_lock(philo->check);
        if (*philo->loop)
        {
            *philo->loop = 0;
            pthread_mutex_unlock(philo->check);
            print_state(tmp - philo->t_0, philo->n, "dead");
        }

    }

    return (0);
}

void    ph_eat(t_philo *philo)
{
    long long   eat_init;
    
    if (!check_dead(philo))
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        change_state(philo);
        eat_init = get_milliseconds();
        philo->last_meal = eat_init;
        pthread_mutex_lock(philo->check);
        if (*philo->loop)
        {
            pthread_mutex_unlock(philo->check);
            print_state(eat_init - philo->t_0, philo->n, "eating");
        }
        while (get_milliseconds() - eat_init < (long long)philo->eat)
            ;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}

void    ph_sleep(t_philo *philo)
{
    long long   sleep_init;
    
    sleep_init = get_milliseconds();
    pthread_mutex_lock(philo->check);
    if (*philo->loop)
    {
        pthread_mutex_unlock(philo->check);
        print_state(sleep_init - philo->t_0, philo->n, "sleeping");
    }
    change_state(philo);
    while (get_milliseconds() - sleep_init < philo->sleep)
        ;
}

void    ph_think(t_philo *philo)
{
    long long   think_init;

    if (!check_dead(philo))
    {
        change_state(philo);
        think_init = get_milliseconds() - philo->t_0;
        pthread_mutex_lock(philo->check);
        if (*philo->loop)
        {
            pthread_mutex_unlock(philo->check);
            print_state(think_init, philo->n, "thinking");
        }
    }
}

void    do_action(t_philo *philo)
{
    if (philo->state == INIT || philo->state == THINK)
        ph_eat(philo);
    else if (philo->state == EAT)
        ph_sleep(philo);
    else if (philo->state == SLEEP)
        ph_think(philo);
}



void    *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    philo->t_0 = get_milliseconds();
    philo->last_meal = philo->t_0;
    while(*philo->loop)
    {
        do_action(philo);
    }
    return (NULL);
}