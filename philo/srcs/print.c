/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:10:54 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/22 13:50:22 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_data *data, int id, char *message)
{
	int	is_alive;

	pthread_mutex_lock(&data->died_mutex);
	is_alive = !data->died;
	pthread_mutex_unlock(&data->died_mutex);
	if (is_alive)
	{
		pthread_mutex_lock(&data->print);
		printf("%zu %d %s\n", get_time() - data->timestamp, id, message);
		pthread_mutex_unlock(&data->print);
	}
}

void	print_died(t_data *data, int id)
{
	pthread_mutex_lock(&data->print);
	printf("%zu %d died\n", get_time() - data->timestamp, id);
	pthread_mutex_unlock(&data->print);
}
