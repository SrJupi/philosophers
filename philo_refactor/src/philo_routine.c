#include <philo_r.h>

void	am_i_dead(t_philo *philo)
{
	if (get_milliseconds() - philo->last_meal > (long long)philo->die)
		set_dead(philo);
}

void	ph_eat(t_philo *philo)
{
	long long	eat_init;

	if (try_get_forks(philo))
	{
		eat_init = print_state(philo, "is eating");
		philo->last_meal = eat_init;
		while (get_milliseconds() - eat_init < philo->eat)
			am_i_dead(philo);
		return_forks(philo);
	}
}

void	ph_sleep(t_philo *philo)
{
	long long	sleep_init;

	sleep_init = print_state(philo, "is sleeping");
	while (get_milliseconds() - sleep_init < philo->sleep)
		am_i_dead(philo);
}

void	ph_think(t_philo *philo)
{
	print_state(philo, "is thinking");
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->n % 2)
		usleep(philo->eat * 1000);
	if (philo->forks_mutex[0] == philo->forks_mutex[1])
	{
		while (get_loop(philo->loop_mutex, philo->loop))
			am_i_dead(philo);
		return (NULL);
	}
	while (get_loop(philo->loop_mutex, philo->loop))
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}
