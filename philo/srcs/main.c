/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/07/24 16:23:03 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
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

void	init_philos(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->number)
	{
		data->philos[i].alive = true;
		data->philos[i].time_left = data->time_to_die;
		data->philos[i].data = data;
		i++;
	}
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
	 	data->number_of_meals = -1;
	data->threads = (pthread_t *)malloc(data->number * sizeof(pthread_t));
	if (!data->threads)
	{
		free(data->mutex);
        exit(ERROR);
	}
	data->philos = (t_philos *)malloc(data->number * sizeof(t_philos));
	if (!data->philos)
	{
		free(data->mutex);
		free(data->threads);
		exit(ERROR);
	}
	init_philos(data);
}
// temp
void	print_data(t_data *data)
{
	printf("number: %d\n", data->number);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("number_of_meals: %d\n", data->number_of_meals);
}

void	*do_something(void *arg)
{
	t_philos	*philos;

	philos = ((t_philos *)arg);
	// pthread_mutex_lock(data->mutex);
	// data->philos[0].time_left = data->thread * 100;
	// pthread_mutex_unlock(data->mutex);
	// usleep(500);
	// printf("HI\n");
	// usleep(500);
	// // print_data(data);
	// printf("data->thread: %d\n", data->thread);
	// usleep(500);
	printf("time_to_eat: %d\n", philos->data->time_to_eat);
	return (SUCCESS);
}

bool	do_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		if (pthread_create(&data->threads[i], NULL, &do_something, (void *)&data->philos[i]) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < data->number)
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
		if (!validate_args(argc, argv))
			return (ERROR);
		ft_bzero(&data, sizeof(data));
		data.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!data.mutex)
			return (ERROR);
		pthread_mutex_init(data.mutex, NULL);
		init_data(&data, argc, argv);
		//temp
		print_data(&data);
		if (do_simulation(&data) == false)
			return (free(data.threads), free(data.philos), pthread_mutex_destroy(data.mutex), free(data.mutex), ERROR);
		pthread_mutex_destroy(data.mutex);
		free(data.mutex);
		free(data.threads);
		free(data.philos);
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
