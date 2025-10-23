/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:10:58 by caida-si          #+#    #+#             */
/*   Updated: 2025/10/23 13:51:40 by caida-si         ###   ########.fr       */
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

int	parse_args(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo n_philo time_die time_eat 
			time_sleep [n_meals]\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_number(av[i]) || ft_atoi(av[i] <= 0))
		{
			printf("Error: invalid argument '%s'\n", av[i]);
			return (1);
		}
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
