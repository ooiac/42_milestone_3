/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:10:58 by caida-si          #+#    #+#             */
/*   Updated: 2025/10/28 14:00:57 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static int	error_msg(int msg, char *arg)
{
	if (msg == 1)
		printf("Usage: ./philo n_philo t_die t_eat t_sleep [n_meals]\n");
	else if (msg == 2)
		printf("Error: invalid argument '%s'\n", arg);
	return (1);
}

int	parse_args(int ac, char **av, t_data *data)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (error_msg(1, NULL));
	i = 1;
	while (i < ac)
	{
		if (!is_number(av[i]) || ft_atoi(av[i]) <= 0)
			return (error_msg(2, av[i]));
		i++;
	}
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->meals_required = -1;
	if (ac == 6)
		data->meals_required = ft_atoi(av[5]);
	data->stop = 0;
	return (0);
}
