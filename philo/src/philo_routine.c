#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void    print_the_shit_I_did(t_philo *philo)
{
    printf("%lld ms %d is here!\n", get_milliseconds() - philo->when_I_was_born,  philo->n);
}

void    *philo_routine(void *data)
{
    t_philo *cast;
    long long tmp;

    cast = (t_philo *)data;
    cast->when_I_was_born = get_milliseconds();
    while(1)
    {
        tmp = get_milliseconds();
        print_the_shit_I_did(cast);
        while (get_milliseconds() - tmp < 500)
        {}
    }
    return (NULL);
}