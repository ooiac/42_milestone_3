/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caida-si <caida-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:51:04 by caida-si          #+#    #+#             */
/*   Updated: 2025/10/27 18:25:24 by caida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meals_required;
	long long		start_time;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
}	t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int				parse_args(int ac, char **av, t_data *data);
int				init_all(t_data *data, t_philo **philos);
void			start_simulation(t_data *data, t_philo *philos);
void			cleanup(t_data *data, t_philo *philos);
long long		get_time(void);
void			print_action(t_philo *philo, char *msg);
void			monitor(t_philo *philos, t_data *data);

#endif