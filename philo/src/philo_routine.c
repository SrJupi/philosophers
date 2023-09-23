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

	if (philo->right_mutex == NULL)
		return ;
	if (try_get_forks(philo))
	{
		change_state(philo);
		eat_init = get_milliseconds();
		if (get_loop(philo->loop_mutex, philo->loop))
		{
			philo->last_meal = eat_init;
			print_state(eat_init - philo->t_0, philo, "eating");
			usleep(philo->data->eat * 1000);
			check_all_meals(philo);
			
		}
		return_forks(philo);
	}
}

void	ph_sleep(t_philo *philo)
{
	long long	sleep_init;

	sleep_init = get_milliseconds();
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		print_state(sleep_init - philo->t_0, philo, "sleeping");
	}
	change_state(philo);
	while (get_milliseconds() - sleep_init < philo->data->sleep)
		am_i_dead(philo);
}

void	ph_think(t_philo *philo)
{
	long long	think_init;

	change_state(philo);
	think_init = get_milliseconds() - philo->t_0;
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		print_state(think_init, philo, "thinking");
	}
}



void	do_routine(t_philo *philo)
{
	int	loop;

	loop = 1;
	while (loop)
	{
		am_i_dead(philo);
		if (philo->state == THINK)
			ph_eat(philo);
		else if (philo->state == EAT)
			ph_sleep(philo);
		else if (philo->state == SLEEP)
			ph_think(philo);

		loop = get_loop(philo->loop_mutex, philo->loop);
	}
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	do_routine(philo);
	return (NULL);
}