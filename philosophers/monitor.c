#include "philo.h"

static int	all_ate_enough(t_philo *philos, t_data *data)
{
	int	i;
	
	if (data->meals_required == -1)
		return 0;
	i = 0;
	while (i < data->nb_philo)
	{
		if (philos[i].meals_eaten < data->meals_required)
			return (0);
		i++;
	}
	return (1);
}

void	monitor(t_philo *philos, t_data *data)
{
	int	i;
	long long now;

	while(!data->stop)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			now = get_time();
			if (now - philos[i].last_meal > data->time_die)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("%lld %d died\n", now - data->start_time, philos[i].id);
				data->stop = 1;
				pthread_mutex_unlock(&data->print_lock);
				return ;
			}
			i++;
		}
		if (all_ate_enough(philos, data))
		{
			data->stop = 1;
			return ;
		}
		usleep(1000);
	}
}