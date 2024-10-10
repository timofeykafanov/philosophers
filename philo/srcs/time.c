/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:04:55 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 12:25:35 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	improved_usleep(long time, t_data *data, t_philos *philo)
{
	long	start;
	int		count;

	start = get_time();
	count = 0;
	(void)data;
	(void)philo;
	while (!data->died && get_time() - start < time)
	{
		// if (count % 10 == 0)
		// {
		// 	philo->time_left -= 1;
		// }
		// if (philo->time_left <= 0)
		// {
		// 	print_status(data, philo->id, "died");
		// 	pthread_mutex_lock(&data->alive);
		// 	data->died = true;
		// 	pthread_mutex_unlock(&data->alive);
		// 	return (false);
		// }
		// pthread_mutex_lock(&data->died_mutex);
		// if (data->died)
		// {
		// 	pthread_mutex_unlock(&data->died_mutex);
		// 	return (false);
		// }
		// pthread_mutex_unlock(&data->died_mutex);
		// count++;
		usleep(100);
	}
	return (true);
}
