/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/03 16:18:02 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

long	get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	improved_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time / 1000)
		usleep(100);
}


void	init_philos(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->number)
	{
		data->philos[i].id = i + 1;
		data->philos[i].alive = true;
		data->philos[i].time_left = data->time_to_die;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->fork[i];
		data->philos[i].right_fork = &data->fork[(i + 1) % data->number];
		data->philos[i].meals = 0;
		i++;
	}
}

bool	init_mutex(t_data *data)
{
	int	i;
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number);
	if (!data->fork)
		exit(false);
	i = 0;
	while (i < data->number)
		pthread_mutex_init(&data->fork[i++], NULL);
	return (true);
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->timestamp = get_time();
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
	 	data->number_of_meals = -1;
	if (init_mutex(data) == false)
		exit(ERROR);
	data->threads = (pthread_t *)malloc(data->number * sizeof(pthread_t));
	if (!data->threads)
	{
		free(data->fork);
        exit(ERROR);
	}
	data->philos = (t_philos *)malloc(data->number * sizeof(t_philos));
	if (!data->philos)
	{
		free(data->fork);
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

void	*philo_routine(void *arg)
{
	t_philos	*philo;
	t_data		*data;

	philo = ((t_philos *)arg);
	data = philo->data;
	while (1)
	{
		if (philo->id % 2 == 0 && get_time() - data->timestamp < 5)
		{
			printf("%zu %d is thinking\n", get_time() - data->timestamp, philo->id);			
			improved_usleep(data->time_to_eat * 1000);
		}
		pthread_mutex_lock(philo->left_fork);
		printf("%zu %d has taken a fork\n", get_time() - data->timestamp, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%zu %d has taken a fork\n", get_time() - data->timestamp, philo->id);
		printf("%zu %d is eating\n", get_time() - data->timestamp, philo->id);
		philo->meals++;
		improved_usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("%zu %d is sleeping\n", get_time() - data->timestamp, philo->id);
        improved_usleep(data->time_to_sleep * 1000);
		printf("%zu %d is thinking\n", get_time() - data->timestamp, philo->id);
	}
	// pthread_mutex_lock(data->mutex);
	// data->philos[0].time_left = data->thread * 100;
	// pthread_mutex_unlock(data->mutex);
	// usleep(500);
	// printf("HI\n");
	// usleep(500);
	// // print_data(data);
	// printf("data->thread: %d\n", data->thread);
	// usleep(500);
	// printf("id: %d\n", philo->data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].data->philos[philo->id].id);
	// return (SUCCESS);
}

bool	do_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		if (pthread_create(&data->threads[i], NULL, &philo_routine, (void *)&data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			return (false);
		}
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
