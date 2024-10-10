/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:15:46 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 14:32:50 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	full_check(t_data *data, int i)
{
	if (data->philos[i].meals >= data->number_of_meals
		&& data->number_of_meals > 0)
	{
		if (data->philos[i].full == false)
			data->full_philos++;
		data->philos[i].full = true;
		if (data->full_philos == data->number)
		{
			pthread_mutex_lock(&data->died_mutex);
			data->died = true;
			pthread_mutex_unlock(&data->died_mutex);
			return (false);
		}
	}
	return (true);
}

bool	death_check(t_data *data, int i)
{
	if (data->philos[i].last_meal + data->time_to_die < get_time())
	{
		pthread_mutex_lock(&data->died_mutex);
		data->died = true;
		pthread_mutex_unlock(&data->died_mutex);
		usleep(1);
		print_status(data, data->philos[i].id, "died");
		return (false);
	}
	return (true);
}
