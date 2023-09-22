#include "philo.h"
#include <stdio.h>

void i_see_dead_people(t_cmd *cmd)
{
    int i;
    int num_meal;
    long long last_meal;
    long long tmp;

    i = 0;
    num_meal = 0;
    while (i < cmd->n_philo)
    {
        last_meal = get_last_meal(cmd->philos[i]);
        tmp = get_milliseconds() - last_meal;
        num_meal += get_meals(cmd->philos[i]);
        if (tmp > cmd->philos[i]->die)
        {
            set_dead(cmd->philos[i], tmp);
            loop_to_zero(cmd->check_mutex, &cmd->loop);
            return ;
        }
        i++;
    }
    if (num_meal >= cmd->max_meal * cmd->n_philo)
    {
        loop_to_zero(cmd->check_mutex, &cmd->loop);
        print_well_fed_message(cmd->check_mutex, cmd->max_meal);
    }
}

void *cmd_routine(void *data)
{  
    t_cmd *cmd;
    int loop;

    cmd = (t_cmd *)data;
    loop = get_loop(cmd->check_mutex, &cmd->loop);
    while (loop)
    {
        i_see_dead_people(cmd);
        loop = get_loop(cmd->check_mutex, &cmd->loop);
    }
    printf("cmd finished - loop: %d\n", cmd->loop);
    return (NULL);   
}