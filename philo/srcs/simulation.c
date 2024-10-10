/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:09:31 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 12:27:55 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*philo_routine(void *arg)
{
	t_philos	*philo;
	t_data		*data;
	long		count;

	philo = ((t_philos *)arg);
	data = philo->data;
	count = 0;
	while (1)
	{
		print_status(data, philo->id, "is thinking");
		if (philo->id % 2 == 0 && count == 0)
			improved_usleep(data->time_to_eat, data, philo);
		pthread_mutex_lock(philo->left_fork);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(data, philo->id, "has taken a fork");
		print_status(data, philo->id, "is eating");
		philo->meals++;
		philo->last_meal = get_time();
		improved_usleep(data->time_to_eat, data, philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_status(data, philo->id, "is sleeping");
		improved_usleep(data->time_to_sleep, data, philo);
		print_status(data, philo->id, "is thinking");
		if (count == 0)
			count++;
	}
	return (SUCCESS);
}

bool	do_simulation(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->number)
	{
		if (pthread_create(&data->threads[i], NULL, &philo_routine, (void *)&data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			return (false);
		}
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < data->number)
		{
			if (data->philos[i].last_meal + data->time_to_die < get_time())
			{
				print_status(data, data->philos[i].id, "died");
				return (false);
			}
			i++;
			usleep(200);
		}
	}
	i = 0;
	while (i < data->number)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}