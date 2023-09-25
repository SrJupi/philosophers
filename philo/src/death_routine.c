#include "philo.h"
#include <stdio.h>

void i_see_dead_people(t_death *death)
{
    int i;
    long long last_meal;
    long long tmp;

    i = 0;
    while (i < death->n_philo)
    {
        last_meal = get_last_meal(death->philos[i]);
        tmp = get_milliseconds() - last_meal;
        if (tmp > death->philos[i].data->die)
        {
            set_dead(&death->philos[i]);
            return ;
        }
        i++;
    }
}

void *death_routine(void *data)
{  
    t_death *death;

    death = (t_death *)data;
    while (get_loop(death->loop_mutex, death->loop))
        i_see_dead_people(death);
    return (NULL);   
}