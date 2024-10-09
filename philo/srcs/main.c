/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkafanov <tkafanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:16:41 by tkafanov          #+#    #+#             */
/*   Updated: 2024/10/09 15:43:21 by tkafanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <unistd.h>

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

void	print_status(t_data *data, int id, char *message)
{
	pthread_mutex_lock(&data->print);
	printf("%zu %d %s\n", get_time() - data->timestamp, id, message);
	pthread_mutex_unlock(&data->print);
}

bool	improved_usleep(long time, t_data *data, t_philos *philo)
{
	long	start;
	int		count;

	start = get_time();
	count = 0;
	(void)data;
	(void)philo;
	while (get_time() - start < time)
	{
		// if (count % 10 == 0)
		// {
		// 	philo->time_left -= 1;
		// }
		// if (philo->time_left <= 0)
		// {
		// 	print_status(data, philo->id, "died");
		// 	pthread_mutex_lock(&data->alive);
		// 	data->died = true;
		// 	pthread_mutex_unlock(&data->alive);
		// 	return (false);
		// }
		// pthread_mutex_lock(&data->died_mutex);
		// if (data->died)
		// {
		// 	pthread_mutex_unlock(&data->died_mutex);
		// 	return (false);
		// }
		// pthread_mutex_unlock(&data->died_mutex);
		// count++;
		usleep(100);
	}
	return (true);
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
	pthread_mutex_init(&data->print, NULL);
	return (true);
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->timestamp = get_time();
	data->died = false;
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
	long		count;

	philo = ((t_philos *)arg);
	data = philo->data;
	count = 0;
	while (1)
	{
		print_status(data, philo->id, "is thinking");
		if (philo->id % 2 == 0 && count == 0)
			improved_usleep(data->time_to_eat, data, philo);
		pthread_mutex_lock(philo->left_fork);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(data, philo->id, "has taken a fork");
		print_status(data, philo->id, "is eating");
		philo->meals++;
		philo->time_left = data->time_to_die;
		improved_usleep(data->time_to_eat, data, philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_status(data, philo->id, "is sleeping");
		improved_usleep(data->time_to_sleep, data, philo);
		print_status(data, philo->id, "is thinking");
		if (count == 0)
			count++;
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
	return (SUCCESS);
}

void	*monitor_routine(void *arg)
{
	t_data		*data;
	t_philos	*philo;

	int	i = 0;
	data = ((t_data *)arg);
	philo = data->philos;
	while (1)
	{
		while (i < data->number)
		{
			if (philo[i].time_left <= 0)
			{
				print_status(data, philo[i].id, "died");
				pthread_mutex_lock(&data->died_mutex);
				data->died = true;
				pthread_mutex_unlock(&data->died_mutex);
				return (NULL);
			}
			i++;
		}
	}
	
	return (NULL);
}

bool	do_simulation(t_data *data)
{
	int			i;
	t_philos	*philo;

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
	pthread_create(&data->monitor, NULL, &monitor_routine, &data);
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
