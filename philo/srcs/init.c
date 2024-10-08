/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:04:16 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 15:52:18 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <time.h>

static void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = data->timestamp;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->fork[i];
		data->philos[i].right_fork = &data->fork[(i + 1) % data->number];
		data->philos[i].meals = 0;
		data->philos[i].full = false;
		i++;
	}
}

static bool	init_mutex(t_data *data)
{
	int	i;

	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* data->number);
	if (!data->fork)
		exit(false);
	i = 0;
	while (i < data->number)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->died_mutex, NULL);
	pthread_mutex_init(&data->is_eating, NULL);
	pthread_mutex_init(&data->meals_mutex, NULL);
	return (true);
}

void	init_agrs(t_data *data, char **argv)
{
	data->number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
}

void	init_data(t_data *data, int argc, char **argv)
{
	init_agrs(data, argv);
	data->timestamp = get_time();
	data->died = false;
	data->full_philos = 0;
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
		data->number_of_meals = -1;
	if (init_mutex(data) == false)
		exit(ERROR);
	data->threads = (pthread_t *)malloc(data->number * sizeof(pthread_t));
	if (!data->threads)
	{
		free(data->fork);
		exit(ERROR);
	}
	data->philos = (t_philos *)malloc(data->number * sizeof(t_philos));
	if (!data->philos)
	{
		free(data->fork);
		free(data->threads);
		exit(ERROR);
	}
	init_philos(data);
}
