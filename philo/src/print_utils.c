#include <philo.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	print_well_fed(t_philo *philo)
{
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		zero_loop(philo->loop_mutex, philo->loop);
		printf("Simulation ended at %lld because all philosophers were full.\
\nThey ate %d meals!!!\n", get_milliseconds() - philo->t_0, *philo->total_meals);
	}
}

static void	check_all_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->meals_mutex);
	*philo->total_meals += 1;
	if (philo->data->max_eat > 0 && *philo->total_meals >= philo->data->max_eat * philo->data->num)
		print_well_fed(philo);
	pthread_mutex_unlock(philo->meals_mutex);		
}

long long	print_state(t_philo *philo, const char *status)
{
	long long 	tmp;
	
	tmp = 0;
	pthread_mutex_lock(philo->print_mutex);
	if (get_loop(philo->loop_mutex, philo->loop))
	{
		tmp = get_milliseconds();
		printf("%lld %d %s\n", tmp - philo->t_0, philo->n, status);
		if (!ft_strcmp(status, "is eating"))
			check_all_meals(philo);
	}
	pthread_mutex_unlock(philo->print_mutex);
	return (tmp);
}