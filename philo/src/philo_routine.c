#include <philo.h>


void am_i_dead(t_philo *philo)
{
	long long tmp;

	tmp = get_milliseconds();	
	if (tmp - philo->last_meal > (long long)philo->data->die)
	{
		set_dead(philo, tmp);
	}
}

void	ph_eat(t_philo *philo)
{
	long long	eat_init;

	if (philo->forks_mutex[1] == NULL)
		return ;
	if (try_get_forks(philo))
	{
		print_state(get_milliseconds() - philo->t_0, philo, "has taken a fork");
		change_state(philo);
		eat_init = get_milliseconds();
		philo->last_meal = eat_init;
		print_state(eat_init - philo->t_0, philo, "is eating");
		while (get_milliseconds() - eat_init < philo->data->eat)
			am_i_dead(philo);
		check_all_meals(philo);
		return_forks(philo);
	}
}

void	ph_sleep(t_philo *philo)
{
	long long	sleep_init;

	sleep_init = get_milliseconds();
	print_state(sleep_init - philo->t_0, philo, "is sleeping");
	change_state(philo);
	while (get_milliseconds() - sleep_init < philo->data->sleep)
		am_i_dead(philo);
}

void	ph_think(t_philo *philo)
{
	long long	think_init;

	change_state(philo);
	think_init = get_milliseconds() - philo->t_0;
	print_state(think_init, philo, "is thinking");
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (get_loop(philo->loop_mutex, philo->loop))
	{
		am_i_dead(philo);
		if (philo->state == THINK)
			ph_eat(philo);
		else if (philo->state == EAT)
			ph_sleep(philo);
		else if (philo->state == SLEEP)
			ph_think(philo);
	}
	return (NULL);
}