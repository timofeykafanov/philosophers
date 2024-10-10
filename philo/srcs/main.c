/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/10 10:11:04 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// temp
void	print_data(t_data *data)
{
	printf("number: %d\n", data->number);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("number_of_meals: %d\n", data->number_of_meals);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!validate_args(argc, argv))
			return (ERROR);
		// ft_bzero(&data, sizeof(data));
		// pthread_mutex_init(data.fork, NULL);
		init_data(&data, argc, argv);
		//temp
		// print_data(&data);
		if (do_simulation(&data) == false)
			return (free(data.threads), free(data.philos), pthread_mutex_destroy(data.fork), free(data.fork), ERROR);
		pthread_mutex_destroy(data.fork);
		free(data.fork);
		free(data.threads);
		free(data.philos);
	}
	else
		return (printf(ERR_MESS_ARGS, argv[0]), ERROR);
	return (SUCCESS);
}
