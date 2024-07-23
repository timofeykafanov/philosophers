/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/23 16:55:46 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

// int counter = 0;
// pthread_mutex_t lock;

// void	*print()
// {
// 	int i = 0;
// 	while (i < 1000000)
// 	{
// 		pthread_mutex_lock(&lock);
// 		i++;
// 		counter++;
// 		pthread_mutex_unlock(&lock);
// 	}
// 	// printf("Hello from threads\n");
// 	// usleep(1);
// 	// printf("Process ID: %d\n", getpid());
// 	return (SUCCESS);
// }

void	init_data(t_data *data, int argc, char **argv)
{
	data->philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
	 	data->number_of_meals = -1;
	data->threads = (pthread_t *)malloc(data->philos * sizeof(pthread_t));
	if (!data->threads)
        exit(ERROR);
}
// temp
void	print_data(t_data *data)
{
	printf("philos: %d\n", data->philos);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("number_of_meals: %d\n", data->number_of_meals);
}

void	*do_something(void *arg)
{
	t_data	*data;

	data = ((t_data *)arg);
	printf("HI\n");
	usleep(2);
	print_data(data);
	return (SUCCESS);
}

bool	do_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		if (pthread_create(&data->threads[i], NULL, &do_something, (void *)data) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < data->philos)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		ft_bzero(&data, sizeof(data));
		if (!validate_args(argc, argv))
			return (ERROR);
		init_data(&data, argc, argv);
		//temp
		print_data(&data);
		if (do_simulation(&data) == false)
			return (free(data.threads), ERROR);
		free(data.threads);
	}
	else
		return (printf(ERR_MESS_ARGS, argv[0]), ERROR);
	// pthread_t t1, t2;
	// pthread_mutex_init(&lock, NULL);
	// if (pthread_create(&t1, NULL, &print, NULL))
	// 	return (ERROR);
	// if (pthread_create(&t2, NULL, &print, NULL))
	// 	return (ERROR);
	// if (pthread_join(t1, NULL))
	// 	return (ERROR);
	// if (pthread_join(t2, NULL))
	// 	return (ERROR);
	// pthread_mutex_destroy(&lock);
	// printf("counter = %d\n", counter);
	return (SUCCESS);
}
