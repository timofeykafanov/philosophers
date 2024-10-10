/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:09:31 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 15:37:10 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

static bool	stop_check(t_data *data)
{
	pthread_mutex_lock(&data->died_mutex);
	if (data->died)
	{
		pthread_mutex_unlock(&data->died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->died_mutex);
	return (false);
}

void	take_forks_and_eat(t_data *data, t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(data, philo->id, "has taken a fork");
	if (philo->last_meal + data->time_to_die > get_time())
		improved_usleep(1, data);
	pthread_mutex_lock(&data->is_eating);
	print_status(data, philo->id, "is eating");
	pthread_mutex_unlock(&data->is_eating);
	philo->last_meal = get_time();
	improved_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->meals++;
}

static void	philo_loop(t_data *data, t_philos *philo, int count)
{
	while (1)
	{
		print_status(data, philo->id, "is thinking");
		if (philo->id % 2 == 0 && count == 0)
			improved_usleep(data->time_to_eat, data);
		take_forks_and_eat(data, philo);
		if (stop_check(data))
			break ;
		print_status(data, philo->id, "is sleeping");
		improved_usleep(data->time_to_sleep, data);
		if (stop_check(data))
			break ;
		print_status(data, philo->id, "is thinking");
		if (count == 0)
			count++;
	}
}

static void	*philo_routine(void *arg)
{
	t_philos	*philo;
	t_data		*data;
	long		count;

	philo = ((t_philos *)arg);
	data = philo->data;
	count = 0;
	philo_loop(data, philo, count);
	return (NULL);
}

bool	do_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		if (pthread_create(&data->threads[i], NULL, \
			&philo_routine, (void *)&data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			return (false);
		}
		i++;
	}
	monitoring_loop(data);
	i = 0;
	while (i < data->number)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}
