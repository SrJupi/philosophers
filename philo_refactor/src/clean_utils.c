#include <philo_r.h>

int	clean_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->philos_t)
		free(data->philos_t);
	if (data->forks_mutex)
		free(data->forks_mutex);
	if (data->forks)
		free(data->forks);
	return (1);
}
