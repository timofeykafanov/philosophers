/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:10:54 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 16:37:10 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_data *data, int id, char *message)
{
	pthread_mutex_lock(&data->print);
	pthread_mutex_lock(&data->died_mutex);
	if (!data->died)
		printf("%zu %d %s\n", get_time() - data->timestamp, id, message);
	pthread_mutex_unlock(&data->died_mutex);
	pthread_mutex_unlock(&data->print);
}
