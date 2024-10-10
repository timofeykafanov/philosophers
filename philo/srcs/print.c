/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:10:54 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 12:43:05 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_data *data, int id, char *message)
{
	pthread_mutex_lock(&data->print);
	printf("%zu %d %s\n", get_time() - data->timestamp, id, message);
	pthread_mutex_unlock(&data->print);
}
