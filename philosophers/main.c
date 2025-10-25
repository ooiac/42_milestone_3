/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:58:38 by caida-si          #+#    #+#             */
/*   Updated: 2025/10/25 20:12:02 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (parse_args(ac, av, &data) == 1)
		return (1);
	if (init_all(&data, &philos) == 1)
		return (1);
	start_simulation(&data, philos);
	cleanup(&data, philos);
	return (0);
}
