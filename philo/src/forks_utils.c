#include <philo.h>

int	try_get_forks(t_philo *philo)
{
	int	ret;
	
	ret = 0;
	lock_forks(philo);
	if (*philo->forks[0] && *philo->forks[1])
	{
		*philo->forks[0] = 0;
		print_state(philo, "has taken a fork");
		*philo->forks[1] = 0;
		print_state(philo, "has taken a fork");
		ret = 1;
	}
	unlock_forks(philo);
	return (ret);
}

void	return_forks(t_philo *philo)
{
	lock_forks(philo);
	*philo->forks[0] = 1;
	*philo->forks[1] = 1;
	unlock_forks(philo);
}

void    lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->forks_mutex[philo->side]);
	pthread_mutex_lock(philo->forks_mutex[(philo->side + 1) % 2]);
}

void    unlock_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->forks_mutex[0]);
    pthread_mutex_unlock(philo->forks_mutex[1]);
}
