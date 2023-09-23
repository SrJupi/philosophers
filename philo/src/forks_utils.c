#include <philo.h>

int	try_get_forks(t_philo *philo)
{
	int	ret;
	
	ret = 0;
	lock_forks(philo);
	if (*philo->left_fork && *philo->right_fork)
	{
		*philo->left_fork = 0;
		*philo->right_fork = 0;
		ret = 1;
	}
	unlock_forks(philo);
	return (ret);
}

void	return_forks(t_philo *philo)
{
	lock_forks(philo);
	*philo->left_fork = 1;
	*philo->right_fork = 1;
	unlock_forks(philo);
}

void    lock_forks(t_philo *philo)
{
	if (philo->n < philo->data->num / 2)
    {
        pthread_mutex_lock(philo->left_mutex);
	    pthread_mutex_lock(philo->right_mutex);
    }
    else
    {
        pthread_mutex_lock(philo->right_mutex);
        pthread_mutex_lock(philo->left_mutex);
    }
}

void    unlock_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_mutex);
    pthread_mutex_unlock(philo->right_mutex);
}
