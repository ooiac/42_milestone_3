/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:17:55 by caida-si          #+#    #+#             */
/*   Updated: 2025/10/27 18:26:59 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (1);
	return (0);
}

static void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		if (i == data->nb_philo - 1)
			philos[i].right_fork = &data->forks[0];
		else
			philos[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

int	init_all(t_data *data, t_philo **philos)
{
	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philos)
		return (1);
	if (init_mutexes(data) == 1)
	{
		free(*philos);
		return (1);
	}
	init_philos(data, *philos);
	return (0);
}
