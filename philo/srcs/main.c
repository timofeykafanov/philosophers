/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/22 13:45:59 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!validate_args(argc, argv))
			return (ERROR);
		init_data(&data, argc, argv);
		if (data.number > 1)
		{
			if (do_simulation(&data) == false)
				return (free(data.threads), free(data.philos), \
				pthread_mutex_destroy(data.fork), free(data.fork), ERROR);
			pthread_mutex_destroy(data.fork);
			free_data(&data);
		}
		else
		{
			one_philo(&data);
			free_data(&data);
		}
	}
	else
		return (printf(ERR_MESS_ARGS, argv[0]), ERROR);
	return (SUCCESS);
}
