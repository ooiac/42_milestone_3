/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:01:17 by caida-si          #+#    #+#             */
/*   Updated: 2025/10/23 14:03:26 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	if (!philo->data->stop)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	*routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!p->data->stop)
	{
		print_action(p, "is thinking");
		pthread_mutex_lock(p->left_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_action(p, "has taken a fork");

		print_action(p, "is eating");
		p->last_meal = get_time();
		usleep(p->data->time_eat * 1000);
		p->meals_eaten++;
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);

		print_action(p, "is_sleeping");
		usleep(p->data->time_sleep * 1000);
	}
	return (NULL);
}

void	start_simulation(t_data *data,t_philo *philos)
{
	int	i;
	data->start_time = get_time();
	i = 0;
	while(1 < data->nb_philo)
	{
		philos[i].last_meal = data->start_time;
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			printf("Error: thread creation failed\n");
			data->stop = 1;
			return ;
		}
		i++;
	}
	monitor(philos, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}