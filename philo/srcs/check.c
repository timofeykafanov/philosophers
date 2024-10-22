/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:15:46 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/22 13:51:38 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	full_check(t_data *data, int i)
{
	pthread_mutex_lock(&data->meals_mutex);
	if (data->philos[i].meals >= data->number_of_meals
		&& data->number_of_meals > 0)
	{
		if (data->philos[i].full == false)
			data->full_philos++;
		data->philos[i].full = true;
		if (data->full_philos == data->number)
		{
			pthread_mutex_unlock(&data->meals_mutex);
			pthread_mutex_lock(&data->died_mutex);
			data->died = true;
			pthread_mutex_unlock(&data->died_mutex);
			return (false);
		}
	}
	pthread_mutex_unlock(&data->meals_mutex);
	return (true);
}

bool	death_check(t_data *data, int i)
{
	pthread_mutex_lock(&data->meals_mutex);
	pthread_mutex_lock(&data->is_eating);
	if (data->philos[i].last_meal + data->time_to_die < get_time())
	{
		pthread_mutex_unlock(&data->is_eating);
		pthread_mutex_lock(&data->died_mutex);
		data->died = true;
		print_died(data, data->philos[i].id);
		pthread_mutex_unlock(&data->died_mutex);
		pthread_mutex_unlock(&data->meals_mutex);
		return (false);
	}
	pthread_mutex_unlock(&data->is_eating);
	pthread_mutex_unlock(&data->meals_mutex);
	return (true);
}

bool	stop_check(t_data *data)
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
