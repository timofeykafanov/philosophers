/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:42:03 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 14:44:32 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	monitoring_loop(t_data *data)
{
	int		i;
	bool	stop;

	i = 0;
	stop = false;
	while (1)
	{
		i = 0;
		while (i < data->number)
		{
			if (!death_check(data, i) || !full_check(data, i))
			{
				stop = true;
				break ;
			}
			i++;
			usleep(1);
		}
		if (stop)
			break ;
	}
}
