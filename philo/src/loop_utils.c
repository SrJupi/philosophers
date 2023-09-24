#include <philo.h>

int	get_loop(pthread_mutex_t *loop_mutex, int *current_loop)
{
	int	ret;

	pthread_mutex_lock(loop_mutex);
	ret = *current_loop;
	pthread_mutex_unlock(loop_mutex);
	return (ret);
}

void	zero_loop(pthread_mutex_t *loop_mutex, int *current_loop)
{
	pthread_mutex_lock(loop_mutex);
	*current_loop = 0;
	pthread_mutex_unlock(loop_mutex);
}