/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:04:55 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 12:42:54 by tkafanov         ###   ########.fr       */
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
	(void)philo;
	pthread_mutex_lock(&data->died_mutex);
	while (!data->died && get_time() - start < time)
	{
		pthread_mutex_unlock(&data->died_mutex);

		usleep(100);
		pthread_mutex_lock(&data->died_mutex);
	}
	pthread_mutex_unlock(&data->died_mutex);
	return (true);
}
